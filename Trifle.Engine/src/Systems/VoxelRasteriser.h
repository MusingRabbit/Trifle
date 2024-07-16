#ifndef VOXELRASTERISER_H
#define VOXELRASTERISER_H

#include "../Core/Types.h"
#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"

#include "../Graphics/Graphics.h"
#include "../Components/Components.h"

#include <map>
#include <vector>

namespace tfl
{
    struct VoxelDrawItem
    {
        glm::vec3 screenPos;
        glm::vec2 scale;
        Colour colour;
    };

    typedef std::vector<VoxelDrawItem> VoxelDrawSet;

    class VoxelRasteriser : public System
    {
        private:
        unsigned int m_imgHeight, m_imgWidth;
        std::map<int, VoxelDrawSet> m_drawMap;

        Canvas m_canvas;

        Colour m_clearColour = Colour(0.0f, 0.0f, 0.0f, 1.0f);
        Colour m_emtpyColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);

        Texture2D* m_screenTexture;

        Entity m_screenEntity;

        void SetImageSize(unsigned int width, unsigned int height);
        bool IsDrawn(Rectangle& rect);

        public:
        VoxelRasteriser(unsigned int id, const SystemContext& context);
        ~VoxelRasteriser();
      
        void Init(unsigned int imgWidth, unsigned int imgHeight);
        void Init() override;
        void Update(float dt) override;
        void OnEntityAdded(unsigned int entityId) override;
        void OnEntityRemoved(unsigned int entityId) override;

        void Clear();
        void FillCanvas();
        void AddDrawItem(const VoxelDrawItem& drawItem);

        void Draw(float dt) override;
        void DrawNow();
    };
}



#endif