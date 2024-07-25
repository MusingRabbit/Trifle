#ifndef VOXELRASTERISER_H
#define VOXELRASTERISER_H

#include "../Core/Types.h"
#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"
#include "../Threading/ThreadPool.h"

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

    struct TextDrawItem
    {
        glm::vec2 screenPos;
        std::string text;
        Colour colour;
    };

    typedef std::vector<VoxelDrawItem> VoxelDrawSet;

    class VoxelRasteriser : public System
    {
        private:
        unsigned int m_imgHeight, m_imgWidth;
        std::map<int, VoxelDrawSet> m_drawMap;
        std::vector<TextDrawItem> m_textItems;

        Canvas m_canvas;

        ThreadPool m_threadPool = ThreadPool((unsigned int)5);

        Colour m_clearColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);
        Colour m_emtpyColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);

        Texture2D* m_screenTexture;

        Entity m_screenEntity;

        void SetImageSize(unsigned int width, unsigned int height);
        bool IsDrawn(const Rectangle& rect);
        void DrawVoxels(const int zDepth, const VoxelDrawSet& voxels);

        public:
        VoxelRasteriser(unsigned int id, const SystemContext& context);
        ~VoxelRasteriser();
      
        void Init(unsigned int imgWidth, unsigned int imgHeight);
        void Init() override;
        void Update() override;
        void OnEntityAdded(unsigned int entityId) override;
        void OnEntityRemoved(unsigned int entityId) override;

        void Clear();
        void FillCanvas();

        void AddDrawItem(const VoxelDrawItem& drawItem);

        void AddDrawItem(const TextDrawItem& drawItem);

        void Draw() override;
        void DrawNow();
    };
}



#endif