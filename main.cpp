#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

/// 💨 Conflict-proof particle hook
class $modify(GalliumParticleHook, CCParticleSystemQuad) {
    void update(float dt) {
        // Prevent particle updates
    }

    void setVisible(bool visible) {
        if (this) CCParticleSystemQuad::setVisible(false);
    }
};

/// ✨ Conflict-proof GameObject hook
class $modify(GalliumGameObjectHook, GameObject) {
    void setVisible(bool visible) {
        if (!this) return;

        // Only force visible if not already
        if (!GameObject::isVisible()) GameObject::setVisible(true);

        // Golden glow post-init
        if (this->m_glowSprite) {
            auto color = this->m_glowSprite->getColor();
            if (color.r == 255 && color.g == 255 && color.b == 255) {
                this->m_glowSprite->setColor({255, 215, 0});
            }
        }
    }

    bool shouldBlendAdditive() {
        return true; // ensures offscreen rendering
    }
};
