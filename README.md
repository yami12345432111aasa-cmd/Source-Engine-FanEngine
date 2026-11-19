# Fan Engine Editor

Base ampliada del editor de escritorio Fan Engine, C++17 y Qt 6.

## Incluido en esta versión
- Ventana principal con menús File, Object y Help.
- Panel Hierarchy con objetos de escena.
- Viewport visual de marcador (todavía no renderiza 3D).
- Panel Inspector de lectura para el objeto seleccionado.
- Panel Assets inicial.
- Consola Output.
- Crear objetos vacíos.
- Guardar y abrir escenas `.fscene` en JSON.
- Workflow de GitHub Actions para compilar Windows x64 y generar un ZIP portable.

## Compilar en GitHub
1. Subí el contenido de este ZIP a la raíz del repositorio.
2. En GitHub, abrí **Actions**.
3. Elegí **Build Fan Engine Editor (Windows Portable)**.
4. Tocá **Run workflow**.
5. Al terminar, abrí la ejecución y descargá `FanEngine-Windows-Portable`.

## Compilar localmente
Necesitás CMake 3.21+, Qt 6.5+ (Widgets) y un compilador C++17.

```bash
cmake -S . -B build
cmake --build build --config Release
```

## Estado honesto
Esto es una base funcional de editor, no un motor 3D completo. El viewport todavía es un marcador: faltan renderer 3D, importadores reales de modelos, materiales, scripting, física, audio, empaquetado de juegos y herramientas de depuración. Linux y PS3 están planificados, no compilados. PS3 requiere toolchain y SDK compatibles.
