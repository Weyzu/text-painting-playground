# Text Painting Playground

Small desktop app simulating external backend-side text coloring. App utilizes a C++ backend with typescript front-end that uses the Vue framework.

## 1. Requirements

* CMake 3.12
* Compiler supporting C++17
* npm 7.21.0

## 2. Compilation 

Windows:
```
cmake .
cmake --build . --config Release
```

macOS:
```
cmake -G Xcode .
cmake --build . --config Release -- CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO
```

## 3. UI Compilation

First set-up:
```
cd ui 
npm install .
```

Build:
```
cd ui
npm run build
```

The built UI is placed in the `dist/` folder. To compile the desktop app with the new UI, the UI buid product should be placed in the `assets/` folder.
