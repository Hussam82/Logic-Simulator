//============================================================================
// Name        : Logic_Simulator.cpp
// Author      : Hussam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

/*<--------------------------- Node Class ------------------------------------->*/
class Node{
	friend ostream& operator<<(ostream& out, const Node& other);
private:
	string name;
	int data;
public:
	/* Default Constructor */
	Node(): name("Node"), data(0)
	{

	}
	/* Non-Default Constructor */
	Node(string name, int data): name(name), data(data)
	{

	}
	/* Setters and Getters */
	int getData() const {
		return data;
	}

	void setData(int data) {
		this->data = data;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string &name) {
		this->name = name;
	}
	/* Methods */
	void AND(Node& node1, Node& node2)
	{
		this->data = node1.data & node2.data;
	}
	void OR(Node& node1, Node& node2)
	{
		this->data = node1.data | node2.data;
	}
	void XOR(Node& node1, Node& node2)
	{
		this->data = node1.data ^ node2.data;
	}
};
ostream& operator<<(ostream& out, const Node& other)
{
	out<<other.name<<": "<<other.data;
	return out;
}


/*<--------------------------- Gate Class (Base Class) ------------------------------------->*/
class Gate{
protected:
	Node* inputNode1;
	Node* inputNode2;
	Node* outputNode;
public:
	/* Default CTOR */
	Gate():
		inputNode1(nullptr), inputNode2(nullptr), outputNode(nullptr)
	{

	}
	/* Non-Default (Parameterized) CTOR */
	Gate(Node* inputNode1, Node* inputNode2, Node* outputNode):
		inputNode1(inputNode1), inputNode2(inputNode2), outputNode(outputNode)
	{

	}
	/* Pure Virtual Function */
	virtual int simulateGate() = 0;

	/* Virtual Destructor */
	virtual ~Gate() {}

	/* Setters and Getters */
	const Node* getInputNode1() const {
		return inputNode1;
	}

	void setInputNode1(Node *inputNode1) {
		this->inputNode1 = inputNode1;
	}

	const Node* getInputNode2() const {
		return inputNode2;
	}

	void setInputNode2(Node *inputNode2) {
		this->inputNode2 = inputNode2;
	}

	const Node* getOutputNode() const {
		return outputNode;
	}

	void setOutputNode(Node *outputNode) {
		this->outputNode = outputNode;
	}
};

/*<--------------------------- Child Classes ------------------------------------->*/
class AndGate : public Gate{
public:
	AndGate() {}
	AndGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->AND(*inputNode1, *inputNode2);
		return outputNode->getData();
	}
};

class OrGate : public Gate{
public:
	OrGate() {}
	OrGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->OR(*inputNode1, *inputNode2);
		return outputNode->getData();
	}
};

class XorGate : public Gate{
public:
	XorGate() {}
	XorGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->XOR(*inputNode1, *inputNode2);
		return outputNode->getData();
	}
};

class NandGate : public Gate{
public:
	NandGate() {}
	NandGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->AND(*inputNode1, *inputNode2);
		outputNode->setData(not(outputNode->getData()));
		return outputNode->getData();
	}
};

class NorGate : public Gate{
public:
	NorGate() {}
	NorGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->OR(*inputNode1, *inputNode2);
		outputNode->setData(not(outputNode->getData()));
		return outputNode->getData();
	}
};

class XnorGate : public Gate{
public:
	XnorGate() {}
	XnorGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->XOR(*inputNode1, *inputNode2);
		outputNode->setData(not(outputNode->getData()));
		return outputNode->getData();
	}
};

class NotGate : public Gate{
public:
	NotGate() {}
	NotGate(Node* input1, Node* input2, Node* output):
		Gate(input1, input2, output)
	{

	}
	int simulateGate()
	{
		outputNode->setData(not(inputNode1->getData()));
		return outputNode->getData();
	}
};


/*<--------------------------- Simulator Class ------------------------------------->*/
class Simulator{
private:
	vector<Node*> nodeVector;
	vector<Gate*> gateVector;
	/* CTOR Private to prevent making any object of that class */
	Simulator()
	{

	}
	/* Delete the copy CTOR */
	Simulator(const Simulator& other) = delete;
public:
	static Simulator& createObject()
	{
		static Simulator simulatorObject;
		return simulatorObject;
	}
	void postNode(Node* node)
	{
		nodeVector.push_back(node);
	}
	void postGate(Gate* gate)
	{
		gateVector.push_back(gate);
	}
	Node* findNode(string nodeName)
	{

		for (Node* node : nodeVector)
		{
			if(nodeName == node->getName())
			{
				return node;
			}
		}
		return 0;
	}
	void startSimulate()
	{
		int gateOutputvalue = 0;
		for (Gate* gate : gateVector)
		{
			gateOutputvalue = gate->simulateGate();
			gateOutputvalue = gateOutputvalue + 1;
		}
	}

	void printAllNodes()
	{
		int sizeOfVector = nodeVector.size();
		Node* currentNode;
		for(int index = 0; index < sizeOfVector; index++)
		{
			currentNode = nodeVector[index];
			cout<<*currentNode<<endl;
		}
	}
	void deleteHeapAllocations()
	{
		for (Gate* gate : gateVector)
		{
			delete gate;
		}
		for (Node* node : nodeVector)
		{
			delete node;
		}
	}
};

/*<--------------------------- GateGenerator Class ------------------------------------->*/
class GateGenerator{
private:
	/* Private Data Members */
	Gate* andGate;
	Gate* orGate;
	Gate* nandGate;
	Gate* xorGate;
	Gate* norGate;
	Gate* xnorGate;
	Gate* notGate;
	Node* node;
	/* Related to inputParse() */
	string line;
	string inputNodeName1;
	string inputNodeName2;
	string outputNodeName;
	string opName;
	Gate* gate;
	Node* inputNodeNew1;
	Node* inputNodeNew2;
	Node* outputNodeNew;
	int newNodeValue;
	string newNodeName;
	string outString;
	/* Private Functions */
	Node* createNode(string nodeName, int nodeValue)
	{
		Simulator& sim = Simulator::createObject();
		node = new Node(nodeName, nodeValue);
		sim.postNode(node);
		return node;
	}
	Gate* createGate(string gateName, Node* n1, Node* n2, Node* n3)
		{
			Simulator& sim = Simulator::createObject();
			/* These nodes will be sent from parseInput() function */
			if(gateName == "AND")
			{
				/* Poly-morphic object */
				andGate = new AndGate(n1, n2, n3);
				sim.postGate(andGate);
				return andGate;
			}
			else if(gateName == "OR")
			{
				/* Poly-morphic object */
				orGate = new OrGate(n1, n2, n3);
				sim.postGate(orGate);
				return orGate;
			}
			else if(gateName == "NAND")
			{
				/* Poly-morphic object */
				nandGate = new NandGate(n1, n2, n3);
				sim.postGate(nandGate);
				return nandGate;
			}
			else if(gateName == "NOR")
			{
				/* Poly-morphic object */
				norGate = new NorGate(n1, n2, n3);
				sim.postGate(norGate);
				return norGate;
			}
			else if(gateName == "XOR")
			{
				/* Poly-morphic object */
				xorGate = new XorGate(n1, n2, n3);
				sim.postGate(xorGate);
				return xorGate;
			}
			else if(gateName == "XNOR")
			{
				/* Poly-morphic object */
				xnorGate = new XnorGate(n1, n2, n3);
				sim.postGate(xnorGate);
				return xnorGate;
			}
			else if(gateName == "NOT")
			{
				/* Poly-morphic object */
				notGate = new NotGate(n1, n2, n3);
				sim.postGate(notGate);
				return notGate;
			}
			return 0;
		}


public:
	GateGenerator():
		andGate(nullptr), orGate(nullptr), nandGate(nullptr), xorGate(nullptr),
		norGate(nullptr), xnorGate(nullptr), notGate(nullptr), node(nullptr), gate(nullptr),
		inputNodeNew1(nullptr), inputNodeNew2(nullptr), outputNodeNew(nullptr), newNodeValue(0),
		newNodeName("Node")
	{


	}
	void parseInput()
	{
		Simulator& sim = Simulator::createObject();
		/* Handling Nodes name and value */
		while(true)
		{
			getline(cin, line);
			istringstream iss(line);
			iss>>opName;
			/* Check for the operation required and act upon it */
			if(opName == "AND" || opName == "OR" || opName == "NAND" || opName == "NOR"
					 || opName == "XOR" || opName == "XNOR")
			{
				iss>>inputNodeName1>>inputNodeName2>>outputNodeName;
				/* Check If these nodes exist or not */
				inputNodeNew1 = sim.findNode(inputNodeName1);
				inputNodeNew2 = sim.findNode(inputNodeName2);
				if(inputNodeNew1 == 0)
				{
					inputNodeNew1 = createNode(inputNodeName1, 0);
				}
				if(inputNodeNew2 == 0)
				{
					inputNodeNew2 = createNode(inputNodeName2, 0);
				}
				outputNodeNew = createNode(outputNodeName, 0);
				gate = createGate(opName, inputNodeNew1, inputNodeNew2, outputNodeNew);
			}
			else if(opName == "NOT")
			{
				iss>>inputNodeName1>>outputNodeName;
				/* Check If these nodes exist or not */
				inputNodeNew1 = sim.findNode(inputNodeName1);
				if(inputNodeNew1 == 0)
				{
					inputNodeNew1 = createNode(inputNodeName1, 0);
				}
				outputNodeNew = createNode(outputNodeName, 0);
				gate = createGate(opName, inputNodeNew1, inputNodeNew1, outputNodeNew);
			}
			else if(opName == "SET")
			{
				iss>>newNodeName>>newNodeValue;
				sim.findNode(newNodeName)->setData(newNodeValue);
			}
			else if(opName == "SIM")
			{
				sim.startSimulate();
			}
			else if(opName == "OUT")
			{
				iss>>outString;
				if(outString == "ALL")
				{
					sim.printAllNodes();
					break;
				}
				else
				{
					Node* outNewNode = sim.findNode(outString);
					cout<<*outNewNode<<endl;
				}
			}
		}
	}
	/* Destructor to delete all the heap allocations */
	~GateGenerator()
	{
		Simulator& sim = Simulator::createObject();
		sim.deleteHeapAllocations();
	}
};


int main() {

	GateGenerator gen;
	gen.parseInput();

	return 0;
}
