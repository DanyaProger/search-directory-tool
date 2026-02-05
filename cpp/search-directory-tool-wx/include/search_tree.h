#ifndef SEARCH_TREE_H_INCLUDED
#define SEARCH_TREE_H_INCLUDED

#include <algorithm>
#include <vector>
#include <wx/string.h>

using namespace std;

class FileTree
{
public:
    class DelimeterFileNameNode
    {
    public:
        long long nodeId;
        long long prevNodeId;

        long long lastMatchedChar;
        wxString fileName;
        wxString fileNameLower;
        bool isDir;
        int depth;

        long long firstNotMatchedLinkedSequence = 0;
        long long firstNotMatchedSequenceInLinkedSequence = 0;
        long long nodeIdOfFirstSequenceInLinkedSequence = -1;

        DelimeterFileNameNode(){}

        DelimeterFileNameNode(long long prevNodeId, wxString fileName, bool isDir)
            : prevNodeId(prevNodeId), fileName(fileName), isDir(isDir)
        {
            fileNameLower = fileName.Lower();
        }
    };

    vector<DelimeterFileNameNode> nodes;

    long long addNode(long long prevNodeId, wxString fileName, bool isDir)
    {
        DelimeterFileNameNode node(prevNodeId, fileName, isDir);
        long long result = node.nodeId = nodes.size();
        node.depth = getNodeDepth(prevNodeId) + 1;
        nodes.push_back(node);

        return result;
    }

    void updateNode(long long nodeId, long long firstNotMatchedLinkedSequence, long long firstNotMatchedSequenceInLinkedSequence, long long nodeIdOfFirstSequenceInLinkedSequence, long long lastMatchedChar)
    {
        nodes[nodeId].firstNotMatchedLinkedSequence = firstNotMatchedLinkedSequence;
        nodes[nodeId].firstNotMatchedSequenceInLinkedSequence = firstNotMatchedSequenceInLinkedSequence;
        nodes[nodeId].nodeIdOfFirstSequenceInLinkedSequence = nodeIdOfFirstSequenceInLinkedSequence;
        nodes[nodeId].lastMatchedChar = lastMatchedChar;
    }

    vector<DelimeterFileNameNode*> getNodesInProcessing(long long nodeId)
    {
        vector<DelimeterFileNameNode*> result;
        long long firstId = nodes[nodeId].nodeIdOfFirstSequenceInLinkedSequence;
        if (firstId != -1)
        {
            while (nodeId != firstId)
            {
                result.push_back(&nodes[nodeId]);
                nodeId = nodes[nodeId].prevNodeId;
            }
            result.push_back(&nodes[firstId]);
            reverse(result.begin(), result.end());
        }
        return result;
    }

    vector<DelimeterFileNameNode*> getNodesInProcessing(long long nodeId, long long nodeIdOfFirstSequenceInLinkedSequence)
    {
        vector<DelimeterFileNameNode*> result;
        long long firstId = nodeIdOfFirstSequenceInLinkedSequence;
        if (firstId != -1)
        {
            while (nodeId != firstId)
            {
                result.push_back(&nodes[nodeId]);
                nodeId = nodes[nodeId].prevNodeId;
            }
            result.push_back(&nodes[firstId]);
            reverse(result.begin(), result.end());
        }
        return result;
    }

    wxString getFullPath(long long nodeId)
    {
        vector<long long> nodesIds;
        while (nodeId != -1)
        {
            nodesIds.push_back(nodeId);
            nodeId = nodes[nodeId].prevNodeId;
        }
        reverse(nodesIds.begin(), nodesIds.end());
        wxString result;
        for (long long id : nodesIds)
        {
            result.Append('\\');
            result.Append(nodes[id].fileName);
        }

        return result;
    }

    bool isDir(long long nodeId)
    {
        if (nodeId == -1)
            return true;
        else
            return nodes[nodeId].isDir;
    }

    long long getPrevNodeId(long long nodeId)
    {
        return nodes[nodeId].prevNodeId;
    }

    wxString getFileName(long long nodeId)
    {
        return nodes[nodeId].fileName;
    }

    long long getNodeLength(long long nodeId)
    {
        return nodes[nodeId].fileName.Length() + 1;
    }

    wxUniChar getNodeChar(long long nodeId, long long i)
    {
        if (i == 0)
            return '\\';
        else
            return nodes[nodeId].fileNameLower.GetChar(i - 1);
    }

    int getNodeDepth(long long nodeId)
    {
        if (nodeId == -1)
            return 0;
        else
            return nodes[nodeId].depth;
    }

    long long getFirstNotMatchedLinkedSequence(long long nodeId)
    {
        return nodes[nodeId].firstNotMatchedLinkedSequence;
    }

    long long getFirstNotMatchedSequenceInLinkedSequence(long long nodeId)
    {
        return nodes[nodeId].firstNotMatchedSequenceInLinkedSequence;
    }

    long long getNodeIdOfFirstSequenceInLinkedSequence(long long nodeId)
    {
        return nodes[nodeId].nodeIdOfFirstSequenceInLinkedSequence;
    }
};

#endif // SEARCH_TREE_H_INCLUDED
