//===--- BannedAtomicIncrementOperatorCheck.cpp - clang-tidy --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BannedAtomicIncrementOperatorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace readability {

void BannedAtomicIncrementOperatorCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  // Finder->addMatcher(functionDecl().bind("x"), this);
  Finder->addMatcher(unaryOperator().bind("op"), this);
}

void BannedAtomicIncrementOperatorCheck::check(
    const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  // const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("x");
  // if (!MatchedDecl->getIdentifier() ||
  // MatchedDecl->getName().startswith("awesome_"))
  //   return;
  // diag(MatchedDecl->getLocation(), "function %0 is insufficiently awesome")
  //     << MatchedDecl;
  // diag(MatchedDecl->getLocation(), "insert 'awesome'", DiagnosticIDs::Note)
  //     << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
  const auto *MatchedOp = Result.Nodes.getNodeAs<UnaryOperator>("op");
  if (MatchedOp->isIncrementDecrementOp() &&
      MatchedOp->getType()->isAtomicType()) {
    diag(MatchedOp->getOperatorLoc(),
         "gRPC style: do not use atomic increment and decrement operators");
    // TODO(hork): implement FixItHint for 4 different types
  }
}

} // namespace readability
} // namespace tidy
} // namespace clang
