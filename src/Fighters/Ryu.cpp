//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu(): Fighter("Ryu",200) {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ryu/Ryu_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ryu/Ryu_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>("../music/05 Ryu.mp3");
        country_position={{14,90},0,{1,1}};
        BackgroundInit(15);
        Idle=ActionInit(5,"Idle");
        Back=ActionInit(6,"Back");
        Forward=ActionInit(6,"Forward");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );

    }

}