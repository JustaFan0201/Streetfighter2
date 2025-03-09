#include "Fighters/Fighter.hpp"
namespace Util {
    void Fighter::BackgroundInit(int picture_number) {
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = "../sencepicture/Battle/"+ GetName() +"/frame ("+num+").png";
            stage_background.push_back(filename);
        }
    }
    
    std::vector<std::string> Fighter::ActionInit(int picture_number,std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = "../sencepicture/Fighters/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }
    
    void Fighter::InitPosition(glm::vec2 position, int side) {
        ActionNow->SetDrawData({position, 0, {side, 1}},
                               {ActionNow->GetScaledSize().x * 3, ActionNow->GetScaledSize().y * 3},
                               2.0f);
        direction = side; // 設定角色初始方向
    }
    
    void Fighter::Upload(ms_t SecPassed) {
        State previous_state = now; // 記錄之前的狀態

        // 移動判斷
        if (Input::IsKeyPressed(Keycode::A)) {
            // 當角色朝右時 (direction > 0)，A 為後退；朝左時 (direction < 0)，A 為前進
            ActionNow->m_Transform.translation.x -= velocity * SecPassed / 1000;
            now = (direction > 0) ? State::Back : State::Forward;
        }
        else if (Input::IsKeyPressed(Keycode::D)) {
            // 當角色朝右時 (direction > 0)，D 為前進；朝左時 (direction < 0)，D 為後退
            ActionNow->m_Transform.translation.x += velocity * SecPassed / 1000;
            now = (direction > 0) ? State::Forward : State::Back;
        }
        else {
            now = State::Idle;
        }

        // 如果狀態改變，則更換動畫
        if (now != previous_state) {
            std::vector<std::string> newFrames;
            switch (now) {
                case State::Idle:
                    newFrames = Idle;
                    break;
                case State::Back:
                    newFrames = Back;
                    break;
                case State::Forward:
                    newFrames = Forward;
                    break;
            }

            // 創建新的 Animation 物件
            auto newAnimation = std::make_shared<Util::Animation>(newFrames, true, 60, true);
            ActionNow->SetDrawable(newAnimation);
        }

        // 邊界檢測並翻轉角色
        float posX = ActionNow->m_Transform.translation.x;
        float maxX = 640 - abs(ActionNow->GetScaledSize().x) * 3 / 2;
        float minX = -640 + abs(ActionNow->GetScaledSize().x) * 3 / 2;

        if (posX > maxX || posX < minX) {
            // 限制角色位置
            ActionNow->m_Transform.translation.x = std::clamp(posX, minX, maxX);
            // 反轉角色朝向
            direction *= -1;  
            ActionNow->m_Transform.scale.x *= -1;
        }
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }
}
