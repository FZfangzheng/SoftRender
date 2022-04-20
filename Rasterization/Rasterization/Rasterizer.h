#pragma once
#include <Eigen/Eigen>
#include <optional>
#include <algorithm>
#include "global.h"
#include "Shader.h"
#include "Triangle.h"

using namespace Eigen;

namespace rst
{
    enum class Buffers
    {
        Color = 1,
        Depth = 2
    };

    inline Buffers operator|(Buffers a, Buffers b)
    {
        return Buffers((int)a | (int)b);
    }

    inline Buffers operator&(Buffers a, Buffers b)
    {
        return Buffers((int)a & (int)b);
    }

    class rasterizer
    {
    public:
        rasterizer(int w, int h);
        void set_texture(Texture tex) { texture = tex; }
        void set_vertex_shader(const VertexShader& vs);
        void set_fragment_shader(const FragmentShader& fs);
        void set_pixel(const Vector2i& point, const Eigen::Vector3f& color);

        void clear(Buffers buff);
        void draw(std::vector<Triangle*>& TriangleList);

        std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }

    private:
        std::optional<Texture> texture;
        FragmentShader fragment_shader;
        VertexShader vertex_shader;

        std::vector<Eigen::Vector3f> frame_buf;
        std::vector<float> depth_buf;

        int width, height;
        int next_id = 0;

        void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
        void rasterize_triangle(const Triangle& t, const std::array<Eigen::Vector3f, 3>& world_pos);
        int get_index(int x, int y);
        int get_next_id() { return next_id++; }  
    };
}