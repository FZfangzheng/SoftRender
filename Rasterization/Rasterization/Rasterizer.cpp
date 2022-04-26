#include <algorithm>
#include "Rasterizer.h"
#include <opencv2/opencv.hpp>
#include <math.h>


// Bresenhamֱ�߻����㷨
void rst::rasterizer::draw_line(Eigen::Vector3f begin, Eigen::Vector3f end)
{
    auto x1 = begin.x();
    auto y1 = begin.y();
    auto x2 = end.x();
    auto y2 = end.y();

    Eigen::Vector3f line_color = { 255, 255, 255 };

    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    //�ο���https://www.jianshu.com/p/fc237110d9d4
    //px��py���ۼ����
    //����Ӧ�����ۼ����err>=0.5ʱ��y��x����Ҫ���и��£�x����1��ʱ��err����dy1/dx1
    //����0.5�Ǹ��㣬���������������*2����ʽ���ұ߱�Ϊ0���õ�2dy1-dx1>=0,�������px
    //px<0��������Ҫ����y�����Լ���������Ҳ����+2dy1����ԭʼ��err����dy1/dx1һ·�����ƿ��Եõ���
    //��px>=0ʱ��������Ҫ����y��px��Ҫ��գ���+2dy1�Ļ�����-2dx��Ҳ����+2*(dy1-dx1)��Ҳ����err��ȥ1һ·�����ƿ��Եõ���
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }
        Eigen::Vector2i point = Eigen::Vector2i(x, y);
        set_pixel(point, line_color);
        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
            {
                px = px + 2 * dy1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y = y + 1;
                }
                else
                {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            //            delay(0);
            Eigen::Vector2i point = Eigen::Vector2i(x, y);
            set_pixel(point, line_color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        Eigen::Vector2i point = Eigen::Vector2i(x, y);
        set_pixel(point, line_color);
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x = x + 1;
                }
                else
                {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            Eigen::Vector2i point = Eigen::Vector2i(x, y);
            set_pixel(point, line_color);
        }
    }
}

// �����߷ֱ��붥���Ŀ�������߲�ˣ�������ͬ��λ����������
static bool insideTriangle(int x, int y, const Vector4f* _v) {
    Vector3f v[3];
    for (int i = 0; i < 3; i++)
        v[i] = { _v[i].x(),_v[i].y(), 1.0 };
    Vector3f f0, f1, f2;
    f0 = v[1].cross(v[0]);
    f1 = v[2].cross(v[1]);
    f2 = v[0].cross(v[2]);
    Vector3f p(x, y, 1.);
    if ((p.dot(f0) * f0.dot(v[2]) > 0) && (p.dot(f1) * f1.dot(v[0]) > 0) && (p.dot(f2) * f2.dot(v[1]) > 0))
        return true;
    return false;
}
// ��ȡ��������
static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector4f* v) {
    float c1 = (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y + v[1].x() * v[2].y() - v[2].x() * v[1].y()) / (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() + v[1].x() * v[2].y() - v[2].x() * v[1].y());
    float c2 = (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y + v[2].x() * v[0].y() - v[0].x() * v[2].y()) / (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() + v[2].x() * v[0].y() - v[0].x() * v[2].y());
    float c3 = (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y + v[0].x() * v[1].y() - v[1].x() * v[0].y()) / (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() + v[0].x() * v[1].y() - v[1].x() * v[0].y());
    return { c1,c2,c3 };
}
// ���ƹ��̣����ö�����ɫ����ƬԪ��ɫ����rasterize_triangle��
void rst::rasterizer::draw() {
    // ����unordered_map obj_map
    for (auto& kv : obj_map) {
        for (const auto& t : kv.second)
        {
            //newtriΪ��Ļ�ռ�����������
            Triangle newtri = *t;
            //���ع۲�ռ�ĵ�λ��,ͬʱ������ɫ����������������
            std::array<Eigen::Vector3f, 3> viewspace_pos = vertex_shader_map[kv.first].use(&newtri, t);
            // ��դ����ʾ������
            rasterize_triangle(kv.first, newtri, viewspace_pos);
        }
    }
}
// ���ƹ��̣����ö�����ɫ����ƬԪ��ɫ����rasterize_triangle��
void rst::rasterizer::draw(std::vector<Triangle*>& TriangleList) {
    for (const auto& t : TriangleList)
    {
        //newtriΪ��Ļ�ռ�����������
        Triangle newtri = *t;
        //���ع۲�ռ�ĵ�λ��,ͬʱ������ɫ����������������
        std::array<Eigen::Vector3f, 3> viewspace_pos = vertex_shader.use(&newtri, t);
        // ��դ����ʾ������
        rasterize_triangle(newtri, viewspace_pos);
    }
}
// ���Ĳ�ֵ
static Eigen::Vector3f interpolate(float alpha, float beta, float gamma, const Eigen::Vector3f& vert1, const Eigen::Vector3f& vert2, const Eigen::Vector3f& vert3, float weight)
{
    return (alpha * vert1 + beta * vert2 + gamma * vert3) / weight;
}

static Eigen::Vector2f interpolate(float alpha, float beta, float gamma, const Eigen::Vector2f& vert1, const Eigen::Vector2f& vert2, const Eigen::Vector2f& vert3, float weight)
{
    auto u = (alpha * vert1[0] + beta * vert2[0] + gamma * vert3[0]);
    auto v = (alpha * vert1[1] + beta * vert2[1] + gamma * vert3[1]);

    u /= weight;
    v /= weight;

    return Eigen::Vector2f(u, v);
}
//��դ�������Σ��ڲ�����ƬԪ��ɫ��
//t������Ļ�ռ������ε����ꡢ�۲�ռ䷨�ߡ�Ĭ����ɫ��view_posΪ�۲�ռ������ε�����
void rst::rasterizer::rasterize_triangle(int idx, const Triangle& t, const std::array<Eigen::Vector3f, 3>& view_pos)
{
    auto v = t.toVector4();
    // ������������
    Vector4f A = v[0];
    Vector4f B = v[1];
    Vector4f C = v[2];
    // bounding box
    float minX = std::min(A[0], std::min(B[0], C[0]));
    float maxX = std::max(A[0], std::max(B[0], C[0]));
    float minY = std::min(A[1], std::min(B[1], C[1]));
    float maxY = std::max(A[1], std::max(B[1], C[1]));
    // ȡ��
    int minX_i = static_cast<int>(std::floor(minX));
    int maxX_i = static_cast<int>(std::ceil(maxX));
    int minY_i = static_cast<int>(std::floor(minY));
    int maxY_i = static_cast<int>(std::ceil(maxY));
    // ����bounding box ��ĵ�
    for (int x = std::max(minX_i, 0); x <= std::min(maxX_i, width - 1); ++x) {
        for (int y = std::max(minY_i, 1); y <= std::min(maxY_i, height); ++y) {
            if (insideTriangle(static_cast<float>(x) + 0.5, static_cast<float>(y) + 0.5, t.v)) {
                //��ȡ���Ĳ�ֵ
                auto tup = computeBarycentric2D(static_cast<float>(x) + 0.5, static_cast<float>(y) + 0.5, t.v);
                float alpha;
                float beta;
                float gamma;
                std::tie(alpha, beta, gamma) = tup;
                float Z = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                float zp = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                zp *= Z;
                // �ж�����Ƿ����������ȣ�����˵��Ӧ����ʾ
                if (zp > depth_buf[get_index(x, y)]) {
                    // color
                    auto interpolated_color = interpolate(alpha, beta, gamma, t.color[0], t.color[1], t.color[2], 1);
                    // normal
                    auto interpolated_normal = interpolate(alpha, beta, gamma, t.normal[0], t.normal[1], t.normal[2], 1).normalized();
                    // texcoords
                    auto interpolated_texcoords = interpolate(alpha, beta, gamma, t.tex_coords[0], t.tex_coords[1], t.tex_coords[2], 1);
                    // shadingcoords
                    auto interpolated_shadingcoords = interpolate(alpha, beta, gamma, view_pos[0], view_pos[1], view_pos[2], 1);

                    // �������ݲ�ֵ����Ľṹ��
                    fragment_shader_payload payload(interpolated_color, interpolated_normal, interpolated_texcoords, texture_map[idx] ? &*texture_map[idx] : nullptr);
                    payload.view_pos = interpolated_shadingcoords;
                    //����ƬԪ��ɫ��
                    auto pixel_color = fragment_shader_map[idx].use(payload);
                    // �������
                    depth_buf[get_index(x, y)] = zp;
                    // ������ɫ
                    set_pixel(Eigen::Vector2i(x, y), pixel_color);
                }
            }
        }
    }

}
//��դ�������Σ��ڲ�����ƬԪ��ɫ��
//t������Ļ�ռ������ε����ꡢ�۲�ռ䷨�ߡ�Ĭ����ɫ��view_posΪ�۲�ռ������ε�����
void rst::rasterizer::rasterize_triangle(const Triangle& t, const std::array<Eigen::Vector3f, 3>& view_pos)
{
    auto v = t.toVector4();
    // ������������
    Vector4f A = v[0];
    Vector4f B = v[1];
    Vector4f C = v[2];
    // bounding box
    float minX = std::min(A[0], std::min(B[0], C[0]));
    float maxX = std::max(A[0], std::max(B[0], C[0]));
    float minY = std::min(A[1], std::min(B[1], C[1]));
    float maxY = std::max(A[1], std::max(B[1], C[1]));
    // ȡ��
    minX = static_cast<int>(std::floor(minX));
    maxX = static_cast<int>(std::ceil(maxX));
    minY = static_cast<int>(std::floor(minY));
    maxY = static_cast<int>(std::ceil(maxY));
    // ����bounding box ��ĵ�
    for (int x = minX; x <= maxX; ++x) {
        for (int y = minY; y <= maxY; ++y) {
            if (insideTriangle(static_cast<float>(x) + 0.5, static_cast<float>(y) + 0.5, t.v)) {
                //��ȡ���Ĳ�ֵ
                auto tup = computeBarycentric2D(static_cast<float>(x) + 0.5, static_cast<float>(y) + 0.5, t.v);
                float alpha;
                float beta;
                float gamma;
                std::tie(alpha, beta, gamma) = tup;
                float Z = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                float zp = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                zp *= Z;
                // �ж�����Ƿ����������ȣ�����˵��Ӧ����ʾ
                if (zp > depth_buf[get_index(x, y)]) {
                    // color
                    auto interpolated_color = interpolate(alpha, beta, gamma, t.color[0], t.color[1], t.color[2], 1);
                    // normal
                    auto interpolated_normal = interpolate(alpha, beta, gamma, t.normal[0], t.normal[1], t.normal[2], 1).normalized();
                    // texcoords
                    auto interpolated_texcoords = interpolate(alpha, beta, gamma, t.tex_coords[0], t.tex_coords[1], t.tex_coords[2], 1);
                    // shadingcoords
                    auto interpolated_shadingcoords = interpolate(alpha, beta, gamma, view_pos[0], view_pos[1], view_pos[2], 1);

                    // �������ݲ�ֵ����Ľṹ��
                    fragment_shader_payload payload(interpolated_color, interpolated_normal, interpolated_texcoords, texture ? &*texture : nullptr);
                    payload.view_pos = interpolated_shadingcoords;
                    //����ƬԪ��ɫ��
                    auto pixel_color = fragment_shader.use(payload);
                    // �������
                    depth_buf[get_index(x, y)] = zp;
                    // ������ɫ
                    set_pixel(Eigen::Vector2i(x, y), pixel_color);
                }
            }
        }
    }

}
// �������֡�������Ȼ���
void rst::rasterizer::clear(rst::Buffers buff)
{
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{ 0, 0, 0 });
    }
    // ���ֵ����Ϊ��С
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
    {
        std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::lowest());
    }
}
// ��ʼ�������С
rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);

    texture = std::nullopt;
}
// ����ά����תΪһά����
int rst::rasterizer::get_index(int x, int y)
{
    return (height - y) * width + x;
    //return x + y * width;
}
// ���֡����
void rst::rasterizer::set_pixel(const Vector2i& point, const Eigen::Vector3f& color)
{
    //int ind = point.x() + point.y() * width;
    int ind = (height - point.y()) * width + point.x();
    frame_buf[ind] = color;
}
// ���ö�����ɫ��
void rst::rasterizer::set_vertex_shader(const VertexShader& vs)
{
    vertex_shader = vs;
}
// ����ƬԪ��ɫ��
void rst::rasterizer::set_fragment_shader(const FragmentShader& fs)
{
    fragment_shader = fs;
}
// ���ö�����ɫ��
void rst::rasterizer::set_vertex_shader(int idx, const VertexShader& vs)
{
    vertex_shader_map.emplace(idx, vs);
}
// ����ƬԪ��ɫ��
void rst::rasterizer::set_fragment_shader(int idx, const FragmentShader& fs)
{
    fragment_shader_map.emplace(idx, fs);
}

