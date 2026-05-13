# AGENTS

## Project Context

- Project: `yr-simd`.
- Domain: runtime patch for `Command & Conquer: Red Alert 2 Yuri's Revenge`.
- Main goal: replace selected `ConvertClass` blitter paths with SIMD implementations.
- Dependency: `YRpp` submodule at `YRpp/`.

## Build Context

- Target platform: Windows `Win32` (`x86`) only.
- Solution/configs: `yr-simd.sln` with `Debug`, `DevBuild`, `Release`.
- Canonical scripts:
  - `scripts/build_debug.bat`
  - `scripts/build_devbuild.bat`
  - `scripts/build_release.bat`

## Repository Conventions

- Keep `yr-simd` naming in project/artifact/config files.
- Keep CI/build settings aligned with existing solution configurations only.
- Do not reintroduce legacy `Spawner` naming.

## Code Style

- Follow Phobos-style C++ conventions.
- Keep changes minimal and targeted.
- Preserve stable fallback behavior when touching SIMD paths.
- Use tabs for indentation and Allman braces.
- Keep pointer style as `Type* pName` and pointer variable prefix `p`.
- Local vars/args: `camelCase`; types/classes/namespaces: `PascalCase`.
- Prefer `constexpr`/inline helpers over new macros when possible.

## Hooking Rules

- Hook names should be descriptive (`HookedFunction_HookPurpose` style).
- Keep `DEFINE_HOOK` size argument correct.
- Keep hook logic readable and avoid unnecessary macro usage.

## SIMD Behavior

- Runtime SIMD selection order: `AVX512 -> AVX2 -> SSE2 -> Scalar`.
- `AVX512` means `AVX512F + AVX512BW + AVX512VL` (plus required OS state support).
- `MaxSimdLevel` clamps autodetected level.
- `MaxSimdLevel=Vanilla` disables SIMD blitter replacement and keeps vanilla blitters.
