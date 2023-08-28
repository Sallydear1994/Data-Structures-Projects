// Digraph_SanityCheckTests.cpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This is a set of "sanity checking" unit tests for your Digraph
// implementation, provided primarily as a mechanism for ensuring
// that your implementation is compatible with the unit tests we'll
// be using to test your implementation during grading, as well as
// to provide simple examples of how each member function is supposed
// to behave.
//
// While you'll certainly want all of these tests to pass before you
// consider yourself done with Digraph, there are plenty of interesting
// cases that are not tested here.  The phrase "sanity checking" was
// chosen for a reason; this is just a cursory check to be sure that
// the basics are in place.  It'll be up to you to round out that
// testing with your own, more thorough testing.

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <gtest/gtest.h>
#include "Digraph.hpp"


TEST(Digraph_SanityCheckTests, canConstructAndDestroy)
{
    Digraph<int, int> d1;
    Digraph<std::string, std::string> d2;
}


TEST(Digraph_SanityCheckTests, canCopyConstructToCompatibleType)
{
    Digraph<unsigned int, std::string> d1;
    Digraph<char, double> d2;

    Digraph<unsigned int, std::string> dd1{d1};
    Digraph<char, double> dd2{d2};
}


TEST(Digraph_SanityCheckTests, canMoveConstructToCompatibleType)
{
    Digraph<int, int> d1;
    Digraph<std::string, std::string> d2;

    Digraph<int, int> dd1 = std::move(d1);
    Digraph<std::string, std::string> dd2 = std::move(d2);
}


TEST(Digraph_SanityCheckTests, canAssignToCompatibleType)
{
    Digraph<std::string, double> d1;
    Digraph<std::string, double> d2;

    Digraph<int, int> d3;
    Digraph<int, int> d4;

    d1 = d2;
    d3 = d4;
}


TEST(Digraph_SanityCheckTests, canMoveAssignToCompatibleType)
{
    Digraph<std::string, double> d1;
    Digraph<std::string, double> d2;

    Digraph<int, int> d3;
    Digraph<int, int> d4;

    d1 = std::move(d2);
    d3 = std::move(d4);
}


TEST(Digraph_SanityCheckTests, canGetAllVertexNumbers)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    std::vector<int> vertices = d1.vertices();

    ASSERT_EQ(3, vertices.size());

    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(1, vertices[0]);
    ASSERT_EQ(2, vertices[1]);
    ASSERT_EQ(3, vertices[2]);
}


TEST(Digraph_SanityCheckTests, canGetAllEdges)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    std::vector<std::pair<int, int>> edges = d1.edges();

    ASSERT_EQ(3, edges.size());

    std::sort(edges.begin(), edges.end());

    ASSERT_EQ(1, edges[0].first);
    ASSERT_EQ(2, edges[0].second);

    ASSERT_EQ(1, edges[1].first);
    ASSERT_EQ(3, edges[1].second);

    ASSERT_EQ(2, edges[2].first);
    ASSERT_EQ(3, edges[2].second);
}


TEST(Digraph_SanityCheckTests, canGetAllEdgesForOneVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    std::vector<std::pair<int, int>> edges = d1.edges(2);

    ASSERT_EQ(1, edges.size());
    ASSERT_EQ(2, edges[0].first);
    ASSERT_EQ(3, edges[0].second);
}


TEST(Digraph_SanityCheckTests, cannotGetEdgesForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_THROW({ d1.edges(4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, canGetVertexInfoForOneVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    ASSERT_EQ("Example1", d1.vertexInfo(1));
    ASSERT_EQ("Example2", d1.vertexInfo(2));
    ASSERT_EQ("Example3", d1.vertexInfo(3));
}


TEST(Digraph_SanityCheckTests, cannotGetVertexInfoForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    ASSERT_THROW({ d1.vertexInfo(4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, canGetEdgeInfoForOneEdge)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_EQ("Edge1", d1.edgeInfo(1, 2));
    ASSERT_EQ("Edge2", d1.edgeInfo(1, 3));
    ASSERT_EQ("Edge3", d1.edgeInfo(2, 3));
}


TEST(Digraph_SanityCheckTests, cannotGetEdgeInfoForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_THROW({ d1.edgeInfo(1, 1); }, DigraphException);
    ASSERT_THROW({ d1.edgeInfo(1, 4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, cannotGetVertexInfoAfterRemovingVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.removeVertex(2);

    ASSERT_THROW({ d1.vertexInfo(2); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, cannotGetEdgeInfoAfterRemovingEdge)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    d1.removeEdge(1, 3);

    ASSERT_THROW({ d1.edgeInfo(1, 3); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, addingVerticesIncreasesVertexCount)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
        ASSERT_EQ(i, d1.vertexCount());
    }
}


TEST(Digraph_SanityCheckTests, addingEdgesIncreasesEdgeCount)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }

    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount());
    }
}


TEST(Digraph_SanityCheckTests, addingEdgesIncreasesEdgeCountFromVertex)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }

    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount(1));
        ASSERT_EQ(0, d1.edgeCount(2));
    }
}


TEST(Digraph_SanityCheckTests, isStronglyConnectedWhenAllPossibleEdgesArePresent)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);

    d1.addEdge(1, 1, 50);
    d1.addEdge(1, 2, 50);
    d1.addEdge(1, 3, 50);
    d1.addEdge(2, 1, 50);
    d1.addEdge(2, 2, 50);
    d1.addEdge(2, 3, 50);
    d1.addEdge(3, 1, 50);
    d1.addEdge(3, 2, 50);
    d1.addEdge(3, 3, 50);

    ASSERT_TRUE(d1.isStronglyConnected());
}


TEST(Digraph_SanityCheckTests, canFindShortestPathWhenNoChoicesAreToBeMade)
{
    Digraph<int, double> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);

    d1.addEdge(1, 2, 5.0);
    d1.addEdge(2, 3, 17.0);

    std::map<int, int> paths = d1.findShortestPaths(
        1,
        [](double edgeInfo)
        {
            return edgeInfo;
        });

    ASSERT_EQ(3, paths.size());

    ASSERT_TRUE(paths.find(1) != paths.end());
    ASSERT_TRUE(paths.find(2) != paths.end());
    ASSERT_TRUE(paths.find(3) != paths.end());

    ASSERT_EQ(1, paths[1]);
    ASSERT_EQ(1, paths[2]);
    ASSERT_EQ(2, paths[3]);
}

