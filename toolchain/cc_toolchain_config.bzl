load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

all_compile_actions = [
    ACTION_NAMES.cc_flags_make_variable,
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.cpp_header_parsing,
]
all_link_actions = [
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(name = "gcc", path = "/usr/bin/clang++"),
        tool_path(name = "g++", path = "usr/bin/clang++"),
        tool_path(name = "ld", path = "/usr/bin/clang++"),
        tool_path(name = "ar", path = "/usr/bin/llvm-ar"),
        tool_path(name = "cpp", path = "usr/bin/clang-cpp"),
        tool_path(name = "gcov", path = "usr/bin/llvm-cov"),
        tool_path(name = "nm", path = "usr/bin/llvm-nm"),
        tool_path(name = "objdump", path = "usr/bin/llvm-objdump"),
        tool_path(name = "strip", path = "usr/bin/llvm-strip"),
        tool_path(name = "clang-tidy", path = "usr/bin/clang-tidy"),
        tool_path(name = "clang-format", path = "usr/bin/clang-format"),
    ]
    features = [
        feature(
            name = "default_compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-isystem", "/usr/lib/llvm-14/include/c++/v1",
                                "-isystem", "/usr/include/clang/14.0.0/include",
                                "-isystem", "/usr/local/include",
                                "-isystem", "/usr/lib/gcc/x86_64-linux-gnu/include",
                                "-isystem", "/usr/lib/gcc/x86_64-linux-gnu",
                                "-isystem", "/usr/include",
                                "-std=c++17",
                                "-stdlib=libc++",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lc++",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]
    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features=features,
        cxx_builtin_include_directories = [ # NEW
            "/usr/include/clang/14.0.0/include",
            "/usr/lib/llvm-14/include/c++/v1",
            "/usr/include/c++/12",
            "/usr/lib/gcc/x86_64-linux-gnu",
            "/usr/lib/gcc/x86_64-linux-gnu/include",
            "/usr/local/include",
            "/usr/include",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths, # NEW
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
