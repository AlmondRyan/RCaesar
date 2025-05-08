# build.ps1 - Build Script for RCaesar on Windows.
# Copyright 2025 (c) Remimwen (Almond "NvKopres" Ryan)

# This script uses PowerShell, which is available by default from Windows 7 onwards.
# If you're still running Windows XP or 2000: congrats on keeping vintage systems alive!
# However, we strongly recommend upgrading for better development experience and security.

# ... Bro, I envy you have a vintage system.
# I really want a vintage system to find the entertainment that in my childhood. Which I can't found it.

# =============== Build Steps ===================
# 1. If no vcpkg in Environment Variable, using git to download vcpkg and run `bootstrap-vcpkg.bat`
# 2. Using vcpkg install `boost-asio` I'm not joking because vcpkg will download lots of dependencies it will take forever.
# 3. Navigate to `frontend/rcaesar-frontend`, install packages using npm.
# 4. Install Electron.
# 5. Navigate to `backend`, using git to clone `websocketpp`
# 6. Run CMake build.
# 7. Run Electron build.
# 8. Start WebSockets Server, and start Electron Frontend.
