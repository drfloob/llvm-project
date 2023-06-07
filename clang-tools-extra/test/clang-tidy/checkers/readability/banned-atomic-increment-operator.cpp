// RUN: %check_clang_tidy %s readability-banned-atomic-increment-operator %t \
// RUN:   --header-filter='.*' --system-headers \
// RUN:   -- -I %t/usr -isystem %t/sys -isystem

#include <memory>

std::atomic<int> i;
i++;
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: gRPC style: do not use atomic increment and decrement operators [readability-banned-atomic-increment-operator]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// Does not trigger the check
i.fetch_add(1);

