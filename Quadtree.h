#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"

// Structure representing a node in the Quadtree
struct FQuadtreeNode
{
    FBox2D Bounds; // 2D bounds of the node
    TArray<USplineComponent*> SplineComponents; // Spline components in this node
    TSharedPtr<FQuadtreeNode> Children[4]; // Pointers to child nodes (subdivisions)

    FQuadtreeNode(const FBox2D& InBounds) : Bounds(InBounds) {}

    bool IsLeafNode() const
    {
        return Children[0] == nullptr;
    }
};

class FQuadtree
{
private:
    TSharedPtr<FQuadtreeNode> RootNode;
    int32 MaxSplinesPerNode;
    int32 MaxDepth;
    bool bVisualizeQuadtree;

public:
    FQuadtree(const FBox2D& WorldBounds, int32 InMaxSplinesPerNode, int32 InMaxDepth);

    void InsertSplineComponent(USplineComponent* SplineComponent);
    void QuerySplinesInArea(const FBox2D& Area, TArray<USplineComponent*>& OutSplines) const;
    void Clear();
    void GetAllSplines(TArray<USplineComponent*>& OutSplines) const;
    void SetVisualizeQuadtree(bool bValue);

private:
    void SubdivideNode(TSharedPtr<FQuadtreeNode> Node, int32 CurrentDepth);
    void InsertSplineIntoNode(TSharedPtr<FQuadtreeNode> Node, USplineComponent* SplineComponent, int32 CurrentDepth);
    void QueryNodeSplinesInArea(TSharedPtr<FQuadtreeNode> Node, const FBox2D& Area, TArray<USplineComponent*>& OutSplines) const;
    void ClearNode(TSharedPtr<FQuadtreeNode> Node);
    void CollectSplines(const TSharedPtr<FQuadtreeNode>& Node, TArray<USplineComponent*>& OutSplines) const;
    void DrawDebugBoxForNode(TSharedPtr<FQuadtreeNode> Node, UWorld* World);
};
