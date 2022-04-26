#include "OBJ_Loader.h"
#include "Model.h"
void Model::loadModel(OBJTYPE objtype, std::vector<Triangle*>& TriangleList) {
    if (objtype == CUBE) {
        for (int i = 0; i < 288; i += 24) {
            Triangle* t = new Triangle();
            for (int j = 0; j < 3; j++) {
                t->setVertex(j, Vector4f(cube_vertices[i + j * 8 + 0], cube_vertices[i + j * 8 + 1], cube_vertices[i + j * 8 + 2], 1.0));
                t->setNormal(j, Vector3f(cube_vertices[i + j * 8 + 3], cube_vertices[i + j * 8 + 4], cube_vertices[i + j * 8 + 5]));
                t->setTexCoord(j, Vector2f(cube_vertices[i + j * 8 + 6], cube_vertices[i + j * 8 + 7]));
            }
            TriangleList.push_back(t);
        }
    }
    if (objtype == PLANE) {
        for (int i = 0; i < 48; i += 24) {
            Triangle* t = new Triangle();
            for (int j = 0; j < 3; j++) {
                t->setVertex(j, Vector4f(plane_vertices[i + j * 8 + 0], plane_vertices[i + j * 8 + 1], plane_vertices[i + j * 8 + 2], 1.0));
                t->setNormal(j, Vector3f(plane_vertices[i + j * 8 + 3], plane_vertices[i + j * 8 + 4], plane_vertices[i + j * 8 + 5]));
                t->setTexCoord(j, Vector2f(plane_vertices[i + j * 8 + 6], plane_vertices[i + j * 8 + 7]));
            }
            TriangleList.push_back(t);
        }
    }
    
}
void Model::loadModel(const std::string path, std::vector<Triangle*>& TriangleList) {
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(path);
    for (auto mesh : Loader.LoadedMeshes)
    {
        for (int i = 0; i < mesh.Vertices.size(); i += 3)
        {
            Triangle* t = new Triangle();
            for (int j = 0; j < 3; j++)
            {
                t->setVertex(j, Vector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0));
                t->setNormal(j, Vector3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
                t->setTexCoord(j, Vector2f(mesh.Vertices[i + j].TextureCoordinate.X, mesh.Vertices[i + j].TextureCoordinate.Y));
            }
            TriangleList.push_back(t);
        }
    }
}
