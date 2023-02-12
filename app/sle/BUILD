load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "sle",
    srcs = glob(["src/**/*.cc"]),
    hdrs = glob(["include/**/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = [
        "//app/linal:linal",
    ]
)
