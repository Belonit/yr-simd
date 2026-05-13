# yr-simd

`yr-simd` is a native C++ plugin/DLL for Yuri's Revenge that replaces selected `ConvertClass` blitters with SIMD-aware implementations.

The project targets x86 and dispatches runtime paths between `Scalar`, `SSE2`, `AVX2`, and `AVX512`.

## Features

- Runtime SIMD detection with safe fallback.
- Optional max SIMD cap from INI (`Vanilla`, `Scalar`, `SSE2`, `AVX2`, `AVX512`).
- Hook-based integration into game startup and blitter allocation flow.
- Build configurations for `Debug`, `DevBuild`, and `Release`.

## Repository Layout

- `src/` - core code, hooks, utilities, and ConvertClass extension logic.
- `src/Ext/ConvertClass/` - SIMD blitter mapping and implementations.
- `scripts/` - local build/clean helper scripts.
- `.github/` - CI workflows and composite build action.
- `YRpp/` - required submodule dependency.

## Requirements

- Windows
- Visual Studio 2022 (MSVC v143 toolset) or Build Tools with MSBuild
- Git

## Clone and Submodules

Clone with submodules:

```bash
git clone --recurse-submodules <repo-url>
```

If already cloned:

```bash
git submodule update --init --recursive
```

## Local Build

From repository root, use the helper scripts:

```bat
scripts\build_debug.bat
scripts\build_devbuild.bat
scripts\build_release.bat
```

Or call the generic wrapper:

```bat
scripts\build.bat DevBuild
```

Outputs are generated into configuration folders in repo root:

- `Debug\`
- `DevBuild\`
- `Release\`

The main binary is `yr-simd.dll` (and `yr-simd.pdb` for non-hardened/dev builds).

## INI Options

Current runtime options loaded by the project:

- `MaxSimdLevel` from section `[Debug]` in `RA2MD.INI`
- `FixTransparencyBlitters` from section `[General]` in rules INI (`INI_Rules`)

### SIMD Level Selection Logic

`yr-simd` automatically detects the best available CPU/OS SIMD level at runtime, then clamps it by `MaxSimdLevel`.

Selection order:

1. `AVX512`
2. `AVX2`
3. `SSE2`
4. `Scalar`

Important notes:

- `AVX512` in this project means `AVX512F + AVX512BW + AVX512VL` (with required OS state support).
- `MaxSimdLevel=Vanilla` disables SIMD blitter replacement and returns vanilla game blitters.

Example:

```ini
[Debug]
MaxSimdLevel=AVX512 ; AVX512/AVX2/SSE2/Scalar/Vanilla

[General]
FixTransparencyBlitters=yes
```

## CI

- `Nightly Build` workflow builds `DevBuild` and uploads artifacts.
- `Release Build` workflow builds `Release`, archives outputs, and uploads to GitHub release.

## License

See [`LICENSE.md`](LICENSE.md).
