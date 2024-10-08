// Distributed under the MIT License.
// See LICENSE.txt for details.

#pragma once

#include <array>
#include <cstddef>
#include <limits>
#include <memory>

#include "DataStructures/Tensor/Tensor.hpp"
#include "Domain/Block.hpp"
#include "Domain/CoordinateMaps/CoordinateMap.hpp"
#include "Domain/FunctionsOfTime/FunctionOfTime.hpp"
#include "Domain/Structure/ElementId.hpp"
#include "Utilities/Gsl.hpp"
#include "Utilities/MakeArray.hpp"

namespace PUP {
class er;
}  // namespace PUP

/*!
 * \ingroup ComputationalDomainGroup
 * \brief The CoordinateMap for the Element from the Logical frame to the
 * `TargetFrame`
 *
 * An ElementMap takes a CoordinateMap for a Block and an ElementId as input,
 * and then "prepends" the correct affine map to the CoordinateMap so that the
 * map corresponds to the coordinate map for the Element rather than the Block.
 * This allows DomainCreators to only specify the maps for the Blocks without
 * worrying about how the domain may be decomposed beyond that.
 */
template <size_t Dim, typename TargetFrame>
class ElementMap {
 public:
  static constexpr size_t dim = Dim;
  using source_frame = Frame::ElementLogical;
  using target_frame = TargetFrame;

  /// \cond HIDDEN_SYMBOLS
  ElementMap() = default;
  /// \endcond

  ElementMap(const ElementId<Dim>& element_id,
             std::unique_ptr<domain::CoordinateMapBase<Frame::BlockLogical,
                                                       TargetFrame, Dim>>
                 block_map);

  /// Construct from an `element_id` within the `block`. The (affine)
  /// ElementLogical to BlockLogical map is determined by the `element_id`. The
  /// BlockLogical to TargetFrame map is determined by the `block`:
  /// - If the block is time-independent: the `block.stationary_map()` is used.
  /// - If the block is time-dependent: The `block.moving_mesh_*_map()` maps
  ///   are used. Which maps are used depends on the TargetFrame.
  ElementMap(const ElementId<Dim>& element_id, const Block<Dim>& block);

  const domain::CoordinateMapBase<Frame::BlockLogical, TargetFrame, Dim>&
  block_map() const {
    return *block_map_;
  }

  template <typename T>
  tnsr::I<T, Dim, TargetFrame> operator()(
      const tnsr::I<T, Dim, Frame::ElementLogical>& source_point,
      const double time = std::numeric_limits<double>::signaling_NaN(),
      const domain::FunctionsOfTimeMap& functions_of_time = {}) const {
    auto block_source_point =
        apply_affine_transformation_to_point(source_point);
    return block_map_->operator()(std::move(block_source_point), time,
                                  functions_of_time);
  }

  template <typename T>
  tnsr::I<T, Dim, Frame::ElementLogical> inverse(
      tnsr::I<T, Dim, TargetFrame> target_point,
      const double time = std::numeric_limits<double>::signaling_NaN(),
      const domain::FunctionsOfTimeMap& functions_of_time = {}) const {
    auto block_source_point{
        block_map_->inverse(std::move(target_point), time, functions_of_time)
            .value()};
    // Apply the affine map to the points
    tnsr::I<T, Dim, Frame::ElementLogical> source_point;
    for (size_t d = 0; d < Dim; ++d) {
      const double inv_jac = 1.0 / gsl::at(map_slope_, d);
      const double temp = gsl::at(map_offset_, d) * inv_jac;
      source_point.get(d) = inv_jac * block_source_point.get(d) - temp;
    }
    return source_point;
  }

  template <typename T>
  InverseJacobian<T, Dim, Frame::ElementLogical, TargetFrame> inv_jacobian(
      const tnsr::I<T, Dim, Frame::ElementLogical>& source_point,
      const double time = std::numeric_limits<double>::signaling_NaN(),
      const domain::FunctionsOfTimeMap& functions_of_time = {}) const {
    auto block_source_point =
        apply_affine_transformation_to_point(source_point);
    auto block_inv_jac = block_map_->inv_jacobian(std::move(block_source_point),
                                                  time, functions_of_time);
    InverseJacobian<T, Dim, Frame::ElementLogical, TargetFrame> inv_jac;
    for (size_t d = 0; d < Dim; ++d) {
      const double inv_jac_in_dir = 1.0 / gsl::at(map_slope_, d);
      for (size_t i = 0; i < Dim; ++i) {
        inv_jac.get(d, i) = inv_jac_in_dir * block_inv_jac.get(d, i);
      }
    }
    return inv_jac;
  }

  template <typename T>
  Jacobian<T, Dim, Frame::ElementLogical, TargetFrame> jacobian(
      const tnsr::I<T, Dim, Frame::ElementLogical>& source_point,
      const double time = std::numeric_limits<double>::signaling_NaN(),
      const domain::FunctionsOfTimeMap& functions_of_time = {}) const {
    auto block_source_point =
        apply_affine_transformation_to_point(source_point);
    auto block_jac = block_map_->jacobian(std::move(block_source_point), time,
                                          functions_of_time);
    Jacobian<T, Dim, Frame::ElementLogical, TargetFrame> jac;
    for (size_t d = 0; d < Dim; ++d) {
      for (size_t i = 0; i < Dim; ++i) {
        jac.get(i, d) = block_jac.get(i, d) * gsl::at(map_slope_, d);
      }
    }
    return jac;
  }

  // NOLINTNEXTLINE(google-runtime-references)
  void pup(PUP::er& p);

 private:
  template <typename T>
  tnsr::I<T, Dim, Frame::BlockLogical> apply_affine_transformation_to_point(
      const tnsr::I<T, Dim, Frame::ElementLogical>& source_point) const {
    tnsr::I<T, Dim, Frame::BlockLogical> block_source_point;
    for (size_t d = 0; d < Dim; ++d) {
      block_source_point.get(d) = source_point.get(d) * gsl::at(map_slope_, d) +
                                  gsl::at(map_offset_, d);
    }
    return block_source_point;
  }

  std::unique_ptr<
      domain::CoordinateMapBase<Frame::BlockLogical, TargetFrame, Dim>>
      block_map_{nullptr};
  // map_slope_[i] = 0.5 * (segment_ids[i].endpoint(Side::Upper) -
  //                        segment_ids[i].endpoint(Side::Lower))
  // Note: the map_slope_ is the jacobian_
  std::array<double, Dim> map_slope_{
      make_array<Dim>(std::numeric_limits<double>::signaling_NaN())};
  // map_offset_[i] = 0.5 * (segment_ids[i].endpoint(Side::Upper) +
  //                         segment_ids[i].endpoint(Side::Lower))
  std::array<double, Dim> map_offset_{
      make_array<Dim>(std::numeric_limits<double>::signaling_NaN())};
};

template <size_t Dim, typename TargetFrame>
ElementMap(ElementId<Dim> element_id,
           std::unique_ptr<
               domain::CoordinateMapBase<Frame::BlockLogical, TargetFrame, Dim>>
               block_map) -> ElementMap<Dim, TargetFrame>;
