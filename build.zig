const std = @import("std");

pub fn build(b: *std.Build) void {
    const exe = b.addExecutable(.{
        .name = "simple_shell",
        .target = b.host,
    });
    exe.linkLibC();
    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.c",
            "src/tokenizer/tokenizer.c",
        },
    });
    b.installArtifact(exe);
    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "run the application");
    run_step.dependOn(&run_exe.step);
}
