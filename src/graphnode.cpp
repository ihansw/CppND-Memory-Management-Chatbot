#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
	// Task 5: chatBot instance is now on stack. No need to delete.
    // delete _chatBot; 
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

// Task 4: exclusive ownership for the child edge. We need to use move() for transferring the input edge's ownership.
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));
}


// Task 5: chatBot instance is being passed with move(). No pointer is needed.
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
  	// Task 5: chatBot instance is now on stack. No need to invalidate.
    //_chatBot = nullptr; // invalidate pointer at source
}


GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
	// Task 4: Since the element of the _childEdges vector is a smart pointer, change it to raw pointer by using get().
    return _childEdges[index].get();
}