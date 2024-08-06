#ifndef VOXELRASTERISER_H
#define VOXELRASTERISER_H

#include "../Core/Types.h"
#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Core/Stopwatch.h"
#include "../Data/Data.h"
#include "../Threading/ThreadPool.h"
#include "../DataStructures/KDTree.h"

#include "../Graphics/Graphics.h"
#include "../Components/Components.h"


#include <map>
#include <vector>


namespace tfl
{
    struct VoxelDrawItem
    {
        size_t id;
        BoundingBox box;
        Colour colour;

        void SetScreenPos(glm::vec3 pos)
        {
            box.min = pos;
        }

        void SetScale(glm::vec2 scale)
        {
            box.max = {box.min.x + scale.x, box.min.y + scale.y, box.min.z};
        }
    };

    struct TextDrawItem
    {
        glm::vec2 screenPos;
        std::string text;
        Colour colour;
    };

    typedef std::vector<VoxelDrawItem> VoxelDrawSet;

    struct ZDepthPredicate : KDNodePredicate
    {
        std::vector<double> pos;

        ZDepthPredicate(std::vector<double> p)
        {
            pos = p;
        }

        bool operator()(const KDNode& rhs) const{
            return pos[2] < rhs.pos[2];
        }
    };

    class VoxelRasteriser : public System
    {
        private:
        size_t m_drawItemCounter;
        unsigned int m_imgHeight, m_imgWidth;
        std::map<int, VoxelDrawSet> m_drawMap;
        std::vector<TextDrawItem> m_textItems;
        Stopwatch m_debugStopwatch;

        //KDTree m_drawTree;
        //std::vector<KDNode> m_treeNodes;

        Canvas m_canvas;

        ThreadPool m_threadPool = ThreadPool((unsigned int)8);

        Colour m_clearColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);
        Colour m_emtpyColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);

        Texture2D* m_screenTexture;

        Entity m_screenEntity;

        void SetImageSize(unsigned int width, unsigned int height);
        bool IsDrawn(const BoundingBox& box);
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