## Glyph benchmark - Master's project.

This project aims to give a benchmark on Spherical Polar Plots glyphs (ODF glyphs) rendering for orientation distribution functions. We used spherical harmonics to synthetize the glyphs.
The project is on C++ based on QT and uses the OpenMP library.
The executable in the folder bin is for MacOSX.
The benchmarks aims to write the execution times for rendering multiple ODF in a window and acess its scalability. The different rendering configurations explored are, in order of addiction, being (0) the most uneffective:

0) Glyph Indexing;
1) Glyph Indexing and instance rendering;
2) Glyph Indexing and instance rendering and ODF symmetry;
3) Glyph Indexing and instance rendering and ODF symmetry and GPU coalescent memory access.

To make the benchmark, we derived the glyphs from the following spherical meshes:

0) Icosahedron (12 vertices, 30 triangles)
1) 2nd  tessellation order of the icosahedron (42 vertices, 30 triangles)
2) 4nd  tessellation order of the icosahedron (162 vertices, 120 triangles)
3) 8nd  tessellation order of the icosahedron (642 vertices, 480 triangles)
4) 16nd tessellation order of the icosahedron (2562 vertices, 1920 triangles)

To do the benchmark, the executable is executed by command line with the following additional arguments:
[tessellation order index] [rendering configuration] [path in system]

The tessellation order index is set by the number before the indices of the meshes used (0, 1, 2, 3 or 4);
The rendering configuration is the set by (0, 1, 2 or 3) as stated earlier.

In the folder Results, there are the benchmark for different meshes, referred by its vertices, and the different rendering configuration made on a Macbook Pro Retina 13'' early 2015. The executable used is in the folder build/bin/macos. The file "HARDI_Glyphs_BenchmarkDataProcessing.ipynb" developed under jupyter notebook process the data generated to generate the FPS X #glyphs plots for the configurations explored in this work.
