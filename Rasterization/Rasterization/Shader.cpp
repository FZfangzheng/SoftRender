#include "Shader.h"
#include "Utils.h"
void VertexShader::setMVPMatrix(Eigen::Matrix4f m, Eigen::Matrix4f v, Eigen::Matrix4f p) {
    model = m;
    view = v;
    projection = p;
    mvp = p * v * m;
}
void VertexShader::setZNearAndZFar(float zNear, float zFar) {
    f1 = (zNear - zFar) / 2.0;
    f2 = (zNear + zFar) / 2.0;
}
std::array<Eigen::Vector3f, 3> VertexShader::use(Triangle* out, Triangle* in) {
    //观察空间的点位置
    std::array<Eigen::Vector4f, 3> mm{
            (view * model * in->v[0]),
            (view * model * in->v[1]),
            (view * model * in->v[2])
    };
    // 将四维点坐标改为三维点坐标存储
    std::array<Eigen::Vector3f, 3> viewspace_pos;
    // 匿名函数取前3个值
    std::transform(mm.begin(), mm.end(), viewspace_pos.begin(), [](Eigen::Vector4f& v) {
        return v.head<3>();
        });
    //乘MVP矩阵变换至裁剪空间
    Eigen::Vector4f v[] = {
            mvp * in->v[0],
            mvp * in->v[1],
            mvp * in->v[2]
    };
    //透视除法
    for (auto& vec : v) {
        vec.x() /= vec.w();
        vec.y() /= vec.w();
        vec.z() /= vec.w();
    }
    // 法线矩阵，MV矩阵的逆矩阵的转置矩阵（观察空间）
    Eigen::Matrix4f inv_trans = (view * model).inverse().transpose();
    Eigen::Vector4f n[] = {
            inv_trans * Utils::to_vec4(in->normal[0], 0.0f),
            inv_trans * Utils::to_vec4(in->normal[1], 0.0f),
            inv_trans * Utils::to_vec4(in->normal[2], 0.0f)
    };
    //视口变换，原vert.x范围是[-1,1]，需映射到[0, width]
    for (auto& vert : v)
    {
        vert.x() = 0.5 * width * (vert.x() + 1.0);
        vert.y() = 0.5 * height * (vert.y() + 1.0);
        vert.z() = vert.z() * f1 + f2;
    }
    //newtri为屏幕空间三角形数据
    for (int i = 0; i < 3; ++i)
    {
        //设定屏幕空间点位置
        out->setVertex(i, v[i]);
    }

    for (int i = 0; i < 3; ++i)
    {
        //设置观察空间法线
        out->setNormal(i, n[i].head<3>());
    }
    //设置初始颜色信息
    out->setColor(0, 148, 121.0, 92.0);
    out->setColor(1, 148, 121.0, 92.0);
    out->setColor(2, 148, 121.0, 92.0);
    return viewspace_pos;
}
void FragmentShader::setLight(PointLight& light) {
    lights.push_back(light);
}
Eigen::Vector3f FragmentShader::use(const fragment_shader_payload& payload) {
    Eigen::Vector3f return_color = { 0, 0, 0 };
    if (payload.texture)
    {
        // 获取纹理坐标的颜色
        return_color = payload.texture->getColor(payload.tex_coords.x(), payload.tex_coords.y());
    }
    Eigen::Vector3f texture_color;
    texture_color << return_color.x(), return_color.y(), return_color.z();

    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f kd = texture_color / 255.f;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

    Eigen::Vector3f amb_light_intensity{ 10, 10, 10 };
    Eigen::Vector3f eye_pos{ 0, 0, 10 };

    float p = 150;

    Eigen::Vector3f color = texture_color;
    Eigen::Vector3f point = payload.view_pos;
    Eigen::Vector3f normal = payload.normal;

    Eigen::Vector3f result_color = { 0, 0, 0 };

    for (auto& light : lights)
    {
        // TODO: For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular* 
        // components are. Then, accumulate that result on the *result_color* object.
        // 光的方向，方向注意是点到光源
        Eigen::Vector3f light_dir = light.getPosition() - point;
        // 视线方向， 方向注意是点到眼睛
        Eigen::Vector3f view_dir = eye_pos - point;
        // 衰减因子，距离平方
        float r = light_dir.dot(light_dir);

        // ambient
        Eigen::Vector3f La = ka.cwiseProduct(amb_light_intensity);
        // diffuse
        Eigen::Vector3f Ld = kd.cwiseProduct(light.getIntensity() / r);
        Ld *= std::max(0.0f, normal.normalized().dot(light_dir.normalized()));
        // specular
        // h半程向量
        Eigen::Vector3f h = (light_dir + view_dir).normalized();
        Eigen::Vector3f Ls = ks.cwiseProduct(light.getIntensity() / r);
        Ls *= std::pow(std::max(0.0f, normal.normalized().dot(h)), p);

        result_color += (La + Ld + Ls);
    }

    return result_color * 255.f;
}