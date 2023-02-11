load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "app",
    srcs = glob(["src/**/*.cc"]),
    deps = [
        "//app/matrix:matrix",
    ],
)
