#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <tuple>
#include <vector>

template<typename _Ty>
struct Pos {
public:
    Pos() : m_xyz({ 0, 0, 0 }) {}

    Pos(_Ty x, _Ty y) : m_xyz({x, y, 0}) {}

    Pos(_Ty x, _Ty y, _Ty z) : m_xyz({x, y, z}) {}

    Pos(const Pos& other) = default;

    Pos(Pos&& other) = default;

    ~Pos() = default;

    Pos& operator=(const Pos& other) = default;

    Pos& operator=(Pos&& other) = default;

    _Ty& x() const {
        return m_xyz[0];
    }

    _Ty& x() {
        return m_xyz[0];
    }

    _Ty& y() const {
        return m_xyz[1];
    }

    _Ty& y() {
        return m_xyz[1];
    }

    _Ty& z() const {
        return m_xyz[2];
    }

    _Ty& z() {
        return m_xyz[2];
    }

    const _Ty* xyz() const {
        return m_xyz.data();
    }

    _Ty* xyz() {
        return m_xyz.data();
    }

private:
    std::array<_Ty, 3> m_xyz;
};

template<typename _Ty>
struct Color {
public:
    Color() : m_rgb({ 0, 0, 0 }) {}

    Color(_Ty r, _Ty g, _Ty b) : m_rgb({r, g, b}) {}

    Color(const Color& other) = default;

    Color(Color&& other) = default;

    ~Color() = default;

    Color& operator=(const Color& other) = default;

    Color& operator=(Color&& other) = default;

    _Ty& r() const {
        return m_rgb[0];
    }

    _Ty& r() {
        return m_rgb[0];
    }

    _Ty& g() const {
        return m_rgb[1];
    }

    _Ty& g() {
        return m_rgb[1];
    }

    _Ty& b() const {
        return m_rgb[2];
    }

    _Ty& b() {
        return m_rgb[2];
    }

    _Ty* rgb() const {
        return m_rgb.data();
    }

    _Ty* rgb() {
        return m_rgb.data();
    }

private:
    std::array<_Ty, 3> m_rgb;
};

template<typename _Ty>
struct Tex2D {
public:
    Tex2D() : m_uv({ 0, 0 }) {}

    Tex2D(_Ty u, _Ty v) : m_uv({u, v}) {}

    Tex2D(const Tex2D& other) = default;

    Tex2D(Tex2D&& other) = default;

    ~Tex2D() = default;

    Tex2D& operator=(const Tex2D& other) = default;

    Tex2D& operator=(Tex2D&& other) = default;

    std::pair<_Ty, _Ty>& uv() const {
        return m_uv;
    }

    std::pair<_Ty, _Ty>& uv() {
        return m_uv;
    }

private:
    std::pair<_Ty, _Ty> m_uv;
};

template<typename _Ty>
struct Normal {
public:
    Normal() : m_normal({ 0, 0, 0 }) {}

    Normal(const std::array<_Ty, 3>& normal) : m_normal(normal) {}

    Normal(const Normal& other) = default;

    Normal(Normal&& other) = default;

    ~Normal() = default;

    Normal& operator=(const Normal& other) = default;

    Normal& operator=(Normal&& other) = default;

    _Ty* xyz() const {
        return m_normal.data();
    }

    _Ty* xyz() {
        return m_normal.data();
    }

private:
    std::array<_Ty, 3> m_normal;
};

template<typename _Ty>
struct Vertex {
public:
    using value_type = _Ty;
    using reference = _Ty&;
    using const_reference = const _Ty&;
    using pointer = _Ty*;
    using const_pointer = const _Ty*;
    using Pos_t = Pos<_Ty>;
    using Color_t = Color<_Ty>;
    using UV = Tex2D<_Ty>;
    using Normal_t = Normal<_Ty>;

    Vertex() : m_data({ 0, 0, 0}) {}

    Vertex(const Pos_t& pos, const Color_t& color, const UV& uv, const Normal_t& normal)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2], uv.uv().first, uv.uv().second, normal.normal()[0], normal.normal()[1], normal.normal()[2] }) {}

    Vertex(Pos_t&& pos, Color_t&& color, UV&& uv, Normal_t&& normal)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2], uv.uv().first, uv.uv().second, normal.normal()[0], normal.normal()[1], normal.normal()[2] }) {}

    Vertex(const Pos_t& pos, const Color_t& color, const UV& uv)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2], uv.uv().first, uv.uv().second }) {}

    Vertex(Pos_t&& pos, Color_t&& color, UV&& uv)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2], uv.uv().first, uv.uv().second }) {}

    Vertex(const Pos_t& pos, const Color_t& color)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2] }) {}

    Vertex(Pos_t&& pos, Color_t&& color)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], color.rgb()[0], color.rgb()[1], color.rgb()[2] }) {}

    Vertex(const Pos_t& pos, const UV& uv)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], uv.uv().first, uv.uv().second }) {}

    Vertex(Pos_t&& pos, UV&& uv)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2], uv.uv().first, uv.uv().second }) {}
    
    Vertex(const Pos_t& pos)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2] }) {}
    
    Vertex(Pos_t&& pos)
        : m_data({ pos.xyz()[0], pos.xyz()[1], pos.xyz()[2] }) {}

    Vertex(const Vertex& other)
        : m_data(other.m_data) {}
    
    Vertex(Vertex&& other)
        : m_data(std::move(other.m_data)) {}
    
    ~Vertex() = default;

    Vertex& operator=(const Vertex& other) {
        m_data = other.m_data;
        return *this;
    }

    Vertex& operator=(Vertex&& other) {
        m_data = std::move(other.m_data);
        return *this;
    }

    _Ty* data() const {
        return m_data.data();
    }

    _Ty* data() {
        return m_data.data();
    }

    size_t size() const {
        return m_data.size();
    }

    size_t size() {
        return m_data.size();
    }

    _Ty& operator[](size_t index) {
        return m_data[index];
    }

    const _Ty& operator[](size_t index) const {
        return m_data[index];
    }

    Pos_t pos() const {
        return Pos_t({ m_data[0], m_data[1], m_data[2] });
    }

    Pos_t pos() {
        return Pos_t({ m_data[0], m_data[1], m_data[2] });
    }

    Color_t color() const {
        return Color_t({ m_data[3], m_data[4], m_data[5] });
    }

    Color_t color() {
        return Color_t({ m_data[3], m_data[4], m_data[5] });
    }

    UV tex() const {
        return UV({ m_data[6], m_data[7] });
    }

    UV tex() {
        return UV({ m_data[6], m_data[7] });
    }

    Normal_t normal() const {
        return Normal_t({ m_data[8], m_data[9], m_data[10] });
    }

    Normal_t normal() {
        return Normal_t({ m_data[8], m_data[9], m_data[10] });
    }

    void set_pos(const Pos_t& pos) {
        m_data[0] = pos.xyz()[0];
        m_data[1] = pos.xyz()[1];
        m_data[2] = pos.xyz()[2];
    }

    void set_pos(Pos_t&& pos) {
        m_data[0] = pos.xyz()[0];
        m_data[1] = pos.xyz()[1];
        m_data[2] = pos.xyz()[2];
    }

    void set_color(const Color_t& color) {
        m_data[3] = color.rgb()[0];
        m_data[4] = color.rgb()[1];
        m_data[5] = color.rgb()[2];
    }

    void set_color(Color_t&& color) {
        m_data[3] = color.rgb()[0];
        m_data[4] = color.rgb()[1];
        m_data[5] = color.rgb()[2];
    }

    void set_tex(const UV& uv) {
        m_data[6] = uv.uv().first;
        m_data[7] = uv.uv().second;
    }

    void set_tex(UV&& uv) {
        m_data[6] = uv.uv().first;
        m_data[7] = uv.uv().second;
    }

    void set_normal(const Normal_t& normal) {
        m_data[8] = normal.normal()[0];
        m_data[9] = normal.normal()[1];
        m_data[10] = normal.normal()[2];
    }

    void set_normal(Normal_t&& normal) {
        m_data[8] = normal.normal()[0];
        m_data[9] = normal.normal()[1];
        m_data[10] = normal.normal()[2];
    }

private:
    std::vector<_Ty> m_data;
};

#endif // !_VERTEX_H_