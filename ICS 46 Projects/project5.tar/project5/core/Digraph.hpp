// Digraph.hpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>


#include <queue>

// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> roadGraph;
    std::vector<std::pair<int, int>> allVertexEdges;
    std::vector<int> vertexNumbers;
    void traverseGraph(int startVertex, std::map<int, bool> &visited) const;

};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> roadGraph;
    std::vector<std::pair<int, int>> allVertexEdges;
    std::vector<int> vertexNumbers;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    try
    {
        std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> roadGraph = d.roadGraph;
        std::vector<std::pair<int, int>> allVertexEdges = d.allVertexEdges;
        std::vector<int> vertexNumbers = d.vertexNumbers;
    }
    catch(...)
    {
        std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> roadGraph;
        std::vector<std::pair<int, int>> allVertexEdges;
        std::vector<int> vertexNumbers;
    }
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> roadGraph;
    std::vector<std::pair<int, int>> allVertexEdges;
    std::vector<int> vertexNumbers;
    std::swap(roadGraph, d.roadGraph);
    std::swap(allVertexEdges, d.allVertexEdges);
    std::swap(vertexNumbers, d.vertexNumbers);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    Digraph* backup = new Digraph(*this);
    try
    {
        roadGraph = d.roadGraph;
        allVertexEdges = d.allVertexEdges;
        vertexNumbers = d.vertexNumbers;
        delete backup;
        return *this;
    }
    catch (...)
    {
        return *backup;
    }
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    std::swap(roadGraph, d.roadGraph);
    std::swap(allVertexEdges, d.allVertexEdges);
    std::swap(vertexNumbers, d.vertexNumbers);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    return vertexNumbers;
    //return std::vector<int>{};
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    return allVertexEdges;
    //return std::vector<std::pair<int, int>>{};
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    if (roadGraph.find(vertex) != roadGraph.end())
    {
        std::vector<std::pair<int, int>> vertexEdges;
        for (auto i = roadGraph.at(vertex).edges.begin(); i != roadGraph.at(vertex).edges.end(); ++i)
        {
            vertexEdges.push_back(std::make_pair(i->fromVertex, i->toVertex));
        }
        return vertexEdges;
    }
    throw DigraphException("That vertex does not exist!");
    //return std::vector<std::pair<int, int>>{};
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    if (roadGraph.find(vertex) != roadGraph.end())
    {
        return roadGraph.at(vertex).vinfo;
    }
    throw DigraphException("That vertex does not exist!");
    //return VertexInfo{};
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if (roadGraph.find(fromVertex) != roadGraph.end() && roadGraph.find(toVertex) != roadGraph.end())
    {
        for (auto i = roadGraph.at(fromVertex).edges.begin(); i != roadGraph.at(fromVertex).edges.end(); ++i)
        {
            if (i->fromVertex == fromVertex && i->toVertex == toVertex)
            {
                return i->einfo;
            }
        }
        throw DigraphException("That edge does not exist!");
    }
    throw DigraphException("One or more of the vertices does not exist!");
    //return EdgeInfo{};
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    for (int i = 0; i < vertexNumbers.size(); i++) // check if vertex already exists
    {
        if (vertexNumbers[i] == vertex)
        {
            throw DigraphException("That vertex number already exists!");
        }
    }
    roadGraph[vertex].vinfo = vinfo;
    vertexNumbers.push_back(vertex);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if (roadGraph.find(fromVertex) != roadGraph.end() && roadGraph.find(toVertex) != roadGraph.end())
    {
        for (int i = 0; i < allVertexEdges.size(); i++)
        {
            if (allVertexEdges[i].first == fromVertex && allVertexEdges[i].second == toVertex)
            {
                throw DigraphException("The edge already exists!");
            }
        }
        DigraphEdge<EdgeInfo> newEdge;
        newEdge.fromVertex = fromVertex;
        newEdge.toVertex = toVertex;
        newEdge.einfo = einfo;
        roadGraph[fromVertex].edges.push_front(newEdge);
        allVertexEdges.push_back(std::make_pair(fromVertex, toVertex));
    }
    else
    {
        throw DigraphException("One or more of the vertices does not exist!");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if (roadGraph.find(vertex) != roadGraph.end())
    {
        for (int i = 0; i < vertexNumbers.size(); i++)
        {
            if (vertexNumbers[i] == vertex)
            {
                vertexNumbers.erase(vertexNumbers.begin() + i);
                break;
            }
        }
        std::vector<int> indexesToDelete;
        for (int i = 0; i < allVertexEdges.size(); i++)
        {
            if (allVertexEdges[i].first == vertex || allVertexEdges[i].second == vertex)
            {
                indexesToDelete.push_back(i);
            }
        }
        for (int i = 0; i < indexesToDelete.size(); i++)
        {
            for (int j = 0; j < allVertexEdges.size(); j++)
            {
                if (allVertexEdges[j].first == vertex || allVertexEdges[j].second == vertex)
                {
                    allVertexEdges.erase(allVertexEdges.begin() + j);
                    break;
                }
            }
        }
        for (int i = 0; i < vertexNumbers.size(); i++)
        {
            for (auto it = roadGraph.at(vertexNumbers[i]).edges.begin(); it != roadGraph.at(vertexNumbers[i]).edges.end(); ++it)
            {
                if (it->toVertex == vertex)
                {
                    roadGraph[vertexNumbers[i]].edges.erase(it);
                    break;
                }
            }
        }
        roadGraph.erase(roadGraph.find(vertex));
    }
    else
    {
        throw DigraphException("Vertex not found!");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if (roadGraph.find(fromVertex) != roadGraph.end() && roadGraph.find(toVertex) != roadGraph.end())
    {
        bool found = false;
        for (int i = 0; i < allVertexEdges.size(); i++)
        {
            if (allVertexEdges[i].first == fromVertex || allVertexEdges[i].second == toVertex)
            {
                found = true;
                allVertexEdges.erase(allVertexEdges.begin() + i);
                break;
            }
        }
        for (auto it = roadGraph.at(fromVertex).edges.begin(); it != roadGraph.at(fromVertex).edges.end(); ++it)
        {
            if (it->fromVertex == fromVertex && it->toVertex == toVertex)
            {
                found = true;
                roadGraph[fromVertex].edges.erase(it);
                break;
            }
        }
        if (!found)
        {
            throw DigraphException("That edge doesn't exist!");
        }
    }
    else
    {
        throw DigraphException("One or more of the vertices doesn't exist!");
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return vertexNumbers.size();
    //return 0;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    return allVertexEdges.size();
    //return 0;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    if (roadGraph.find(vertex) != roadGraph.end())
    {
        return roadGraph.at(vertex).edges.size();
    }
    throw DigraphException("That vertex does not exist!");
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    for (int i = 0; i < vertexNumbers.size(); i++)
    {
        std::map<int, bool> visited;
        for (int j: vertexNumbers)
        {
            visited[j] = false;
        }
        traverseGraph(vertexNumbers[i], visited);
        for (auto k: vertexNumbers)
        {
            if (!visited[k])
            {
                return false;
            }
        }
    }
    return true;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::traverseGraph(int vertex, std::map<int, bool> &visited) const
{
    auto currentVertex = roadGraph.at(vertex).edges.begin();
    while (currentVertex != roadGraph.at(vertex).edges.end())
    {
        if (!visited[currentVertex->fromVertex])
        {
            visited[currentVertex->fromVertex] = true;
        }
        if (!visited[currentVertex->toVertex])
        {
            traverseGraph(currentVertex->toVertex, visited);
        }
        ++currentVertex;
    }
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    std::map<int, bool> pathKnownForVertex;
    std::map<int, int> previousVertex;
    std::map<double, double> shortestPathForVertex;
    
    for (int i = 0; i < vertexNumbers.size(); i++)
    {
        pathKnownForVertex[vertexNumbers[i]] = false;
        previousVertex[vertexNumbers[i]] = vertexNumbers[i]; // means unknown
        if (vertexNumbers[i] == startVertex)
        {
            shortestPathForVertex[vertexNumbers[i]] = 0.00;
        }
        else
        {
            shortestPathForVertex[vertexNumbers[i]] = 9999999.00; // 9999999 represents infinity
        }
    }

    std::priority_queue<int, std::vector<int>, std::less<int>> pq;
    pq.push(startVertex);

    while (!pq.empty())
    {
        int v = pq.top();
        pq.pop();

        if (!pathKnownForVertex[v])
        {
            pathKnownForVertex[v] = true;
            for (auto it = roadGraph.at(v).edges.begin(); it != roadGraph.at(v).edges.end(); ++it)
            {
                int w = it->toVertex;
                if (shortestPathForVertex[w] > shortestPathForVertex[v] + edgeWeightFunc(it->einfo))
                {
                    shortestPathForVertex[w] = shortestPathForVertex[v] + edgeWeightFunc(it->einfo);
                    previousVertex[w] = v;
                    pq.push(w);
                }
            }
        }
    }
   return previousVertex;
    //return std::map<int, int>{};
}



#endif

