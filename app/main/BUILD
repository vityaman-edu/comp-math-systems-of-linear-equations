load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "app",
    srcs = glob(["**/*.cc"]),
    deps = [
        "//math/linal:lib",
        "//math/sle:lib",
    ],
)
