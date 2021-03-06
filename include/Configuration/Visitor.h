/// \file Visitor.h
/// \brief Definition of class for creating lambda-based visitors for boost::variant
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#ifndef INCLUDE_CONFIGURATION_VISITOR_H_
#define INCLUDE_CONFIGURATION_VISITOR_H_

#include "VisitorImplementation.h"
#include <boost/variant/apply_visitor.hpp>

namespace AliceO2 {
namespace Configuration {
namespace Visitor {

/// Creates a boost::variant visitor with functions.
///
/// Example:
/// \snippet test/TestExamples.cxx [Visitor]
///
/// \tparam ReturnType Return type of the visitor.
/// \tparam Types of the lambda functions.
/// \param functions Functions. One for each type that can be visited.
template<typename ReturnType, typename ... Functions>
Implementation::Visitor<ReturnType, Functions...> make(Functions ... functions)
{
  return {functions...};
}

/// Convenience function to create a boost::variant visitor with functions and immediately apply it.
///
/// Example:
/// \snippet test/TestExamples.cxx [Apply visitor]
///
/// \tparam ReturnType Return type of the visitor.
/// \tparam Variant Type of the variant.
/// \tparam Functions Types of the lambda functions.
/// \param variant The variant to apply the visitor to.
/// \param functions Functions. One for each type that can be visited.
template<typename ReturnType = void, typename Variant, typename ... Functions>
ReturnType apply(const Variant& variant, Functions ... functions)
{
  return boost::apply_visitor(Visitor::make<ReturnType>(functions...), variant);
}

} // namespace Visitor
} // namespace Configuration
} // namespace AliceO2

#endif /* INCLUDE_CONFIGURATION_VISITOR_H_ */
