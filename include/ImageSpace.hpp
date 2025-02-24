//
// Created by asus on 2025/2/25.
//

#ifndef IMAGESPACE_HPP
#define IMAGESPACE_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/TransformUtils.hpp"
namespace Util {
    class ImageSpace : public GameObject {
    public:
        ImageSpace(const std::string &imagePath, float zIndex = 0.0f)
            : GameObject(std::make_shared<Image>(imagePath), zIndex) {}

        void custom_Draw() {
            if (!m_Visible || m_Drawable == nullptr) {
                return;
            }

            auto data = Util::ConvertToUniformBufferData(
                m_Transform, custom_size, m_ZIndex);
            data.m_Model = glm::translate(
                data.m_Model, glm::vec3{m_Pivot / custom_size, 0} * -1.0F);

            m_Drawable->Draw(data);
        }
        void SetDraw(Transform transform,glm::vec2 size,float index) {
            custom_size=size;
            m_Transform=transform;
            SetZIndex(index);
        }
        std::shared_ptr<Core::Drawable> GetDrawable() {
            return m_Drawable;
        }
    private:
        glm::vec2 custom_size;
    };
} // namespace Util
#endif //IMAGESPACE_HPP
