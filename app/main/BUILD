load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "app",
    srcs = glob(["src/**/*.cc"]),
    deps = [
        "//app/linal:linal",
        "//app/sle:sle",
    ],
)
