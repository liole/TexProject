#include "TexProject_Script_Parser.h"
using namespace TexProject;
using namespace std;


#include <TexProject/TexProject_Script_Translator.h>

#include <stack>
#include <algorithm>

#pragma region Translator Accepts

void					Instruction::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Block::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Definition::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expression::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Operator::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Operators::Binary::Assignment::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Storage::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Storages::Literal::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Storages::Variable::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Storages::In::Accept(Translator* translator)
{
	translator->translate(this);
}
void					Instructions::Expressions::Storages::Out::Accept(Translator* translator)
{
	translator->translate(this);
}

void					Instructions::Expressions::Operators::BinaryOperator::Accept(Translator* translator)
{
	//translator->translate(this);
}
void					Instructions::Expressions::Operators::Binary::Plus::Accept(Translator* translator)
{
	//translator->translate(this);
}
void					Instructions::Expressions::Operators::Binary::Minus::Accept(Translator* translator)
{
	//translator->translate(this);
}
void					Instructions::Expressions::Operators::Binary::Multiply::Accept(Translator* translator)
{
	//translator->translate(this);
}
void					Instructions::Expressions::Operators::Binary::Divide::Accept(Translator* translator)
{
	//translator->translate(this);
}

#pragma endregion

#pragma region Visitor Accepts

void					Instruction::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Block::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Definition::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expression::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operator::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::Binary::Assignment::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Storage::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Storages::Literal::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Storages::Variable::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Storages::In::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Storages::Out::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::BinaryOperator::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::Binary::Plus::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::Binary::Minus::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::Binary::Multiply::Accept(Visitor* visitor)
{
	visitor->visit(this);
}
void					Instructions::Expressions::Operators::Binary::Divide::Accept(Visitor* visitor)
{
	visitor->visit(this);
}

#pragma endregion

std::string Expressions::Storage::TypeNames[(unsigned int)Expressions::Storage::Type::__size__] = {
	"bool", "int", "float",
	"vec2", "ivec2",
	"vec3", "ivec3",
	"vec4", "ivec4",
	"mat2", "mat3", "mat4",
	"1D", "2D", "3D", "Cube"
};


#pragma region Tree destructors

Block::~Block()
{
	for (auto i : content)
		delete i;
}
Definition::~Definition()
{
	//delete storage;
	if (initializer)
		delete initializer;
}
Expressions::Storages::Literal::~Literal()
{
	delete value;
}
Expressions::Operators::BinaryOperator::~BinaryOperator()
{
	delete left;
	delete right;
}
Expressions::Operators::Binary::Assignment::~Assignment()
{
	//delete left;
	delete right;
}

#pragma endregion

#pragma region Parser
Parser::Parser(vector<Token*> tkns) :
tokens(tkns)
{
	storages.insert(make_pair("x", new Expressions::Storages::In(Expressions::Storage::Type::Int, nullptr)));
	storages.insert(make_pair("y", new Expressions::Storages::In(Expressions::Storage::Type::Int, nullptr)));
	storages.insert(make_pair("z", new Expressions::Storages::In(Expressions::Storage::Type::Int, nullptr)));
	storages.insert(make_pair("face", new Expressions::Storages::In(Expressions::Storage::Type::Int, nullptr)));
	storages.insert(make_pair("dx", new Expressions::Storages::In(Expressions::Storage::Type::Float, nullptr)));
	storages.insert(make_pair("dy", new Expressions::Storages::In(Expressions::Storage::Type::Float, nullptr)));
	storages.insert(make_pair("dz", new Expressions::Storages::In(Expressions::Storage::Type::Float, nullptr)));
}

Block* Parser::parse()
{
	tokens.insert(tokens.begin(), Token::createToken(Token::Type::Operator, "{"));
	tokens.push_back(Token::createToken(Token::Type::Operator, "}"));
	return isBlock(tokens.begin());
}

bool Parser::isOperator(TokenIter& iter)
{
	return (*iter)->getTokenType() == Token::Type::Operator;
}
bool Parser::isOperator(TokenIter& iter, std::string op)
{
	if (isOperator(iter) &&
		((OperatorToken*)(*iter))->getValue() == op)
	{
		iter++;
		return true;
	}
	else return false;
}


bool Parser::isKeyword(TokenIter& iter)
{
	return (*iter)->getTokenType() == Token::Type::Keyword;
}
bool Parser::isKeyword(TokenIter& iter, std::string kw)
{
	if (isKeyword(iter) &&
		((OperatorToken*)(*iter))->getValue() == kw)
	{
		iter++;
		return true;
	}
	else return false;
}

bool Parser::isIdentifier(TokenIter& iter)
{
	return ((*iter)->getTokenType() == Token::Type::Identifier);
}

std::string Parser::getIdentifier(TokenIter& iter)
{
	string name = ((IdentifierToken*)(*iter))->getValue();
	iter++;
	return name;
}
Expressions::Storage::Type* Parser::isTypeName(TokenIter& iter)
{
	for (int i = 0; i < (int)Expressions::Storage::Type::__size__; ++i)
	if (isKeyword(iter, Expressions::Storage::TypeNames[i]))
		return new Expressions::Storage::Type((Expressions::Storage::Type)i);
	return nullptr;
}

Block* Parser::isBlock(TokenIter& iter)
{
	if (!isOperator(iter, "{"))
		return nullptr;

	Block* block = new Block();
	Instruction* instruction;
	while (instruction = isInstruction(iter))
		block->content.push_back(instruction);

	if (!isOperator(iter, "}"))
		throw ParserError(*iter, "Expecting '}'");

	return block;
}

Instruction* Parser::isInstruction(TokenIter& iter)
{
	Instruction* instruction;
	if ((instruction = isDefinition(iter)) ||
		((instruction = isAssignment(iter)) && isOperator(iter, ";")))
		return instruction;
	if (isEmptyInstruction(iter))
		return new Instruction();
	return nullptr;
}

bool Parser::isEmptyInstruction(TokenIter& iter)
{
	return isOperator(iter, ";");
}

Expressions::Storages::Literal* Parser::isIntegerLiteral(TokenIter& iter)
{
	if (!((*iter)->getTokenType() == Token::Type::IntegerLiteral))
		return nullptr;
	return new Expressions::Storages::Literal(
		Expressions::Storage::Type::Int,
		new int(((IntegerLiteralToken*)(*iter++))->getValue()));
}
Expressions::Storages::Literal* Parser::isRealLiteral(TokenIter& iter)
{
	if (!((*iter)->getTokenType() == Token::Type::RealLiteral))
		return nullptr;
	return new Expressions::Storages::Literal(
		Expressions::Storage::Type::Float,
		new float(((RealLiteralToken*)(*iter++))->getValue()));
}
Expressions::Storages::Literal* Parser::isBoolLiteral(TokenIter& iter)
{
	if (isKeyword(iter, "true"))
		return new Expressions::Storages::Literal(
		Expressions::Storage::Type::Bool,
		new bool(true));
	else if (isKeyword(iter, "false"))
		return new Expressions::Storages::Literal(
		Expressions::Storage::Type::Bool,
		new bool(true));
	else return nullptr;
}
Expressions::Storages::Literal* Parser::isVecMatLiteral(TokenIter& iter)
{
	if (auto type = isTypeName(iter))
	{
		int literalCount;
		switch (*type)
		{
		case Expressions::Storage::Type::Vec2:
		case Expressions::Storage::Type::IVec2:
			literalCount = 2;
			break;
		case Expressions::Storage::Type::Vec3:
		case Expressions::Storage::Type::IVec3:
			literalCount = 3;
			break;
		case Expressions::Storage::Type::Vec4:
		case Expressions::Storage::Type::IVec4:
			literalCount = 4;
			break;
		case Expressions::Storage::Type::Mat2:
			literalCount = 4;
			break;
		case Expressions::Storage::Type::Mat3:
			literalCount = 9;
			break;
		case Expressions::Storage::Type::Mat4:
			literalCount = 16;
			break;
		default:
			iter--;
			return nullptr;
		}
		bool literalTypeFloat = true;
		if (*type == Expressions::Storage::Type::IVec2 ||
			*type == Expressions::Storage::Type::IVec3 ||
			*type == Expressions::Storage::Type::IVec4)
			literalTypeFloat = false;
		if (!isOperator(iter, "("))
			throw ParserError(*iter, "Expecting '('");
		Expressions::Storages::Literal *res = new Expressions::Storages::Literal(*type, nullptr);
		if (literalTypeFloat)
		{
			float *data = new float[literalCount];
			for (int i = 0; i < literalCount; ++i)
			{
				if (auto lit = isRealLiteral(iter))
				{
					data[i] = *(float*)lit->value;
					delete lit;
				}
				else throw ParserError(*iter, "Expecting real literal");
				if (i != literalCount - 1 && !isOperator(iter, ","))
					throw ParserError(*iter, "Expecting ','");
			}
			switch (*type)
			{
			case Expressions::Storage::Type::Vec2:
			{
													 vec2 *resVec2 = new vec2;
													 resVec2->x = data[0];
													 resVec2->y = data[1];
													 res->value = resVec2;
													 break;
			}
			case Expressions::Storage::Type::Vec3:
			{
													 vec3 *resVec3 = new vec3;
													 resVec3->x = data[0];
													 resVec3->y = data[1];
													 resVec3->z = data[2];
													 res->value = resVec3;
													 break;
			}
			case Expressions::Storage::Type::Vec4:
			{
													 vec4 *resVec4 = new vec4;
													 resVec4->x = data[0];
													 resVec4->y = data[1];
													 resVec4->z = data[2];
													 resVec4->w = data[3];
													 res->value = resVec4;
													 break;
			}
			case Expressions::Storage::Type::Mat2:
			{
													 mat2 *resMat2 = new mat2;
													 for (int i = 0; i < 4; ++i)
														 resMat2->val[i] = data[i];
													 res->value = resMat2;
													 break;
			}
			case Expressions::Storage::Type::Mat3:
			{
													 mat3 *resMat3 = new mat3;
													 for (int i = 0; i < 9; ++i)
														 resMat3->val[i] = data[i];
													 res->value = resMat3;
													 break;
			}
			case Expressions::Storage::Type::Mat4:
			{
													 mat4 *resMat4 = new mat4;
													 for (int i = 0; i < 16; ++i)
														 resMat4->val[i] = data[i];
													 res->value = resMat4;
													 break;
			}
			}
			delete[] data;
		}
		else
		{
			int *data = new int[literalCount];
			for (int i = 0; i < literalCount; ++i)
			{
				if (auto lit = isIntegerLiteral(iter))
				{
					data[i] = *(int*)lit->value;
					delete lit;
				}
				else throw ParserError(*iter, "Expecting integer literal");
				if (i != literalCount - 1 && !isOperator(iter, ","))
					throw ParserError(*iter, "Expecting ','");
			}
			switch (*type)
			{
			case Expressions::Storage::Type::IVec2:
			{
													  ivec2 *resVec2 = new ivec2;
													  resVec2->x = data[0];
													  resVec2->y = data[1];
													  res->value = resVec2;
													  break;
			}
			case Expressions::Storage::Type::IVec3:
			{
													  ivec3 *resVec3 = new ivec3;
													  resVec3->x = data[0];
													  resVec3->y = data[1];
													  resVec3->z = data[2];
													  res->value = resVec3;
													  break;
			}
			case Expressions::Storage::Type::IVec4:
			{
													  ivec4 *resVec4 = new ivec4;
													  resVec4->x = data[0];
													  resVec4->y = data[1];
													  resVec4->z = data[2];
													  resVec4->w = data[3];
													  res->value = resVec4;
													  break;
			}
			}
			delete[] data;
		}
		if (!isOperator(iter, ")"))
			throw ParserError(*iter, "Expecting ')");
		return res;
	}
	else return nullptr;
}
Expressions::Storages::Literal* Parser::isLiteral(TokenIter& iter)
{
	Expressions::Storages::Literal* lit;
	if ((lit = isIntegerLiteral(iter)) ||
		(lit = isRealLiteral(iter)) ||
		(lit = isBoolLiteral(iter)) ||
		(lit = isVecMatLiteral(iter)))
		return lit;
	else return nullptr;
}

Definition* Parser::isDefinition(TokenIter& iter)
{
	Definition* def = new Definition;
	bool qualifier = false;
	if (isKeyword(iter, "in")) {
		def->storage = new Expressions::Storages::In;
		qualifier = true;
	}
	else if (isKeyword(iter, "out")) {
		def->storage = new Expressions::Storages::Out;
		qualifier = true;
	}
	else
		def->storage = new Expressions::Storages::Variable;
	if (auto type = isTypeName(iter))
	{
		def->storage->type = *type;
		delete type;
	}
	else if (qualifier)
		throw ParserError(*iter, "Expecting identifier type");
	else return nullptr;

	if (isIdentifier(iter))
	{
		string identifier = getIdentifier(iter);
		if (storages.find(identifier) == storages.end())
			storages.insert(make_pair(identifier, def->storage));
		else
			throw ParserError(*iter, "Identifier redefinition");
	}
	else throw ParserError(*iter, "Expecting identifier name");

	if (isOperator(iter, "="))
	if (auto init = isExpression(iter))
		def->initializer = init;
	else throw ParserError(*iter, "Expecting initialization");

	if (!isOperator(iter, ";"))
		throw ParserError(*iter, "Expecting ';'");
	return def;
}
/*
std::string Properties[] = {
	"red", "green", "blue", "alpha"
};
*/
Expressions::Storage* Parser::isStorage(TokenIter& iter)
{
	if (auto lit = isLiteral(iter))
		return lit;
	if (isIdentifier(iter))
	{
		auto range = storages.equal_range(getIdentifier(iter));
		if (range.first != range.second)
		{
			// for now
			return range.first->second;
		}
		else throw ParserError(*iter, "Undefined variable");
	}
	else return nullptr;
}
Expressions::Operators::Binary::Assignment* Parser::isAssignment(TokenIter& iter)
{
	Expressions::Operators::Binary::Assignment* assig = new Expressions::Operators::Binary::Assignment;
	auto begIter = iter;
	if (auto stor = isStorage(iter))
	{
		assig->left = dynamic_cast<Expressions::Storages::Variable*>(stor);
		if (assig->left == nullptr)
		{
			iter = begIter;
			return nullptr;
		}
	}
	else return nullptr;

	if (!isOperator(iter, "="))
	{
		iter--;
		delete assig;
		return nullptr;
	}
	if (auto expr = isExpression(iter))
		assig->right = expr;
	else throw ParserError(*iter, "Expecting expression");

	//if (!isOperator(iter, ";"))
	//	throw ParserError(*iter, "Expecting ';'");

	return assig;
}
Expressions::Operators::BinaryOperator* Parser::isBinaryOperator(TokenIter& iter)
{
	if (isOperator(iter, "+"))
		return new Expressions::Operators::Binary::Plus();
	if (isOperator(iter, "-"))
		return new Expressions::Operators::Binary::Minus();
	if (isOperator(iter, "*"))
		return new Expressions::Operators::Binary::Multiply();
	if (isOperator(iter, "/"))
		return new Expressions::Operators::Binary::Divide();
	return nullptr;
}
struct OpStackElement
{
	enum Type {
		_BinaryOperator,/* _Function,*/ _Parenthesis
	} type;
	union Value
	{
		Expressions::Operators::BinaryOperator* _binaryOperator;
		/*Function* _function;*/
		void* _parenthesis;
	} value;
};
Expression* Parser::isExpression(TokenIter& iter)
{
	if (auto asig = isAssignment(iter))
		return asig;
	stack<OpStackElement> opStack;
	stack<Expression*> out;
	TokenIter tmp = iter;
	int parenthesisCount = 0;
	while (iter != tokens.end())
	{
		if (auto stor = isStorage(iter))
			out.push(stor);
		/*
		else if (auto func = isFunctionToken(iter))
		{
		func->arguments.push_back(nullptr); // argument reservation
		OpStackElement elem;
		elem.type = OpStackElement::Type::_Function;
		elem.value._function = func;
		opStack.push(elem);
		}
		*/
		/*
		else if (isOperator(iter, ","))
		{
		while (!opStack.empty() && opStack.top().type != OpStackElement::Type::_Parenthesis)
		{
		//if (opStack.top().type != OpStackElement::Type::_Operator)
		//	throw ParserError(Token::createToken(Token::Type::Identifier, opStack.top().value._function->name),
		//	"Expecting operator");

		Expressions::Operators::Binary::BinaryOperator* curr = opStack.top().value._binaryOperator; opStack.pop();
		curr->right = out.top(); out.pop();
		curr->left = out.top(); out.pop();
		out.push(curr);
		}
		if (opStack.empty()) // may be comma expression
		{
		iter--;
		break;
		}
		OpStackElement par = opStack.top();
		opStack.pop();
		if (opStack.top().type != OpStackElement::Type::_Function)
		throw ParserError(*iter, "Separator can be used only in function calls");
		opStack.top().value._function->arguments.push_back(nullptr); // argument reservation
		opStack.push(par);
		}
		*/
		else if (auto op = isBinaryOperator(iter))
		{
			while (!opStack.empty() && opStack.top().type == OpStackElement::Type::_BinaryOperator &&
				op->priority() <= opStack.top().value._binaryOperator->priority())
			{
				Expressions::Operators::BinaryOperator* curr = opStack.top().value._binaryOperator; opStack.pop();
				curr->right = out.top(); out.pop();
				curr->left = out.top(); out.pop();
				out.push(curr);
			}
			OpStackElement elem;
			elem.type = OpStackElement::Type::_BinaryOperator;
			elem.value._binaryOperator = op;
			opStack.push(elem);
		}
		else if (isOperator(iter, "("))
		{
			OpStackElement elem;
			elem.type = OpStackElement::Type::_Parenthesis;
			opStack.push(elem);
			parenthesisCount++;
		}
		else if (isOperator(iter, ")"))
		{
			if (parenthesisCount == 0)
			{
				iter--;
				break;
			}

			parenthesisCount--;
			while (!opStack.empty() && opStack.top().type != OpStackElement::Type::_Parenthesis)
			{
				//if (opStack.top().type != OpStackElement::Type::_BinaryOperator)
				//	throw ParserError(Token::createToken(Token::Type::Identifier, opStack.top().value._function->name),
				//	"Expecting operator");
				Expressions::Operators::BinaryOperator* curr = opStack.top().value._binaryOperator; opStack.pop();
				curr->right = out.top(); out.pop();
				curr->left = out.top(); out.pop();
				out.push(curr);
			}
			if (!opStack.empty())
				opStack.pop();
			else throw ParserError(*iter, "Parenthesis mismatch");
			//if (opStack.top().type == OpStackElement::Type::_Function)
			//{
			//	Function* func = opStack.top().value._function;
			//	for (int i = func->arguments.size() - 1; i >= 0; --i)
			//	{
			//		func->arguments[i] = out.top();
			//		out.pop();
			//	}
			//	out.push(func);
			//}
		}
		else break;
	}
	while (!opStack.empty() && opStack.top().type == OpStackElement::Type::_BinaryOperator)
	{
		Expressions::Operators::BinaryOperator* curr = opStack.top().value._binaryOperator; opStack.pop();
		curr->right = out.top(); out.pop();
		curr->left = out.top(); out.pop();
		out.push(curr);
	}
	if (!opStack.empty())
		throw ParserError(Token::createToken(Token::Type::Operator, "("),
		"Parenthesis mismatch");
	if (out.empty())
	{
		iter = tmp;
		return nullptr;
	}
	if (out.size() != 1)
		throw ParserError(Token::createToken(Token::Type::Operator, "?"),
		"Error in expression");
	return out.top();
}

std::multimap <std::string, Expressions::Storage*>* Parser::getStorages()
{
	return &storages;
}

Parser::~Parser()
{
	for (auto st : storages)
		delete st.second;
}
#pragma endregion

#pragma region TreeSerializer

TreeSerializer::TreeSerializer(std::multimap <std::string, Instructions::Expressions::Storage*>* _storages, std::ostream& _os) :
storages(_storages),
os(&_os),
level(0)
{
}

void TreeSerializer::tabulate()
{
	for (int i = 0; i < level; ++i)
		(*os) << "    ";
}

void TreeSerializer::visit(Instruction* root)
{
	tabulate();
	(*os) << "Instruction" << endl;
}
void TreeSerializer::visit(Instructions::Block* root)
{
	tabulate();
	(*os) << "Block" << endl;
	level++;
	for (auto instr : root->content)
		instr->Accept(this);
	level--;
}
void TreeSerializer::visit(Instructions::Definition* root)
{
	tabulate();
	(*os) << "Definition" << endl;
	level++;
	root->storage->Accept(this);
	if (root->initializer)
	{
		tabulate();
		(*os) << " (initializer)" << endl;
		root->initializer->Accept(this);
	}
	level--;
}
void TreeSerializer::visit(Instructions::Expression* root)
{
	tabulate();
	(*os) << "Expression" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Operator* root)
{
	tabulate();
	(*os) << "Operator" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::Binary::Assignment* root)
{
	tabulate();
	(*os) << "Assignment" << endl;
	level++;
	tabulate();
	(*os) << " (left)" << endl;
	root->left->Accept(this);
	tabulate();
	(*os) << " (right)" << endl;
	root->right->Accept(this);
	level--;
}
void TreeSerializer::visit(Instructions::Expressions::Storage* root)
{
	tabulate();
	(*os) << "Storage" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Storages::Literal* root)
{
	tabulate();
	(*os) << "Literal ";
	switch (root->GetStorageType())
	{
	case Instructions::Expressions::Storage::Type::Bool:
		(*os) << boolalpha << *(bool*)root->value;
		break;
	case Instructions::Expressions::Storage::Type::Float:
		(*os) << *(float*)root->value;
		break;
	case Instructions::Expressions::Storage::Type::Int:
		(*os) << *(int*)root->value;
		break;
	case Instructions::Expressions::Storage::Type::IVec2:
		(*os) << "ivec2(...)"; //<< *(ivec2*)root->value << ")";
		break;
	case Instructions::Expressions::Storage::Type::IVec3:
		(*os) << "ivec3(...)"; //<< *(ivec3*)root->value << ")";
		break;
	case Instructions::Expressions::Storage::Type::IVec4:
		(*os) << "ivec4(...)"; //<< *(ivec4*)root->value << ")";
		break;
	case Instructions::Expressions::Storage::Type::Mat2:
		(*os) << "mat2(...)";
		break;
	case Instructions::Expressions::Storage::Type::Mat3:
		(*os) << "mat3(...)";
		break;
	case Instructions::Expressions::Storage::Type::Mat4:
		(*os) << "mat4(...)";
		break;
	case Instructions::Expressions::Storage::Type::Vec2:
		(*os) << "vec2(...)"; //<< *(vec2*)root->value << ")";
		break;
	case Instructions::Expressions::Storage::Type::Vec3:
		(*os) << "vec3(...)"; //<< *(vec3*)root->value << ")";
		break;
	case Instructions::Expressions::Storage::Type::Vec4:
		(*os) << "vec4(...)"; //<< *(vec4*)root->value << ")";
		break;
	}
	(*os) << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Storages::Variable* root)
{
	tabulate();
	auto iter = find_if(storages->begin(), storages->end(), [root](pair<string, Instructions::Expressions::Storage*> el){
		return el.second == root; });
		(*os) << "Variable '" << iter->first << "'" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Storages::In* root)
{
	tabulate();
	auto iter = find_if(storages->begin(), storages->end(), [root](pair<string, Instructions::Expressions::Storage*> el){
		return el.second == root; });
		(*os) << "IN '" << iter->first << "'" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Storages::Out* root)
{
	tabulate();
	auto iter = find_if(storages->begin(), storages->end(), [root](pair<string, Instructions::Expressions::Storage*> el){
		return el.second == root; });
		(*os) << "OUT '" << iter->first << "'" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::BinaryOperator* root)
{
	tabulate();
	(*os) << "Binary operator" << endl;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::Binary::Plus* root)
{
	tabulate();
	(*os) << "+ operator" << endl;
	level++;
	tabulate();
	(*os) << " (left)" << endl;
	root->left->Accept(this);
	tabulate();
	(*os) << " (right)" << endl;
	root->right->Accept(this);
	level--;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::Binary::Minus* root)
{
	tabulate();
	(*os) << "- operator" << endl;
	level++;
	tabulate();
	(*os) << " (left)" << endl;
	root->left->Accept(this);
	tabulate();
	(*os) << " (right)" << endl;
	root->right->Accept(this);
	level--;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::Binary::Multiply* root)
{
	tabulate();
	(*os) << "* operator" << endl;
	level++;
	tabulate();
	(*os) << " (left)" << endl;
	root->left->Accept(this);
	tabulate();
	(*os) << " (right)" << endl;
	root->right->Accept(this);
	level--;
}
void TreeSerializer::visit(Instructions::Expressions::Operators::Binary::Divide* root)
{
	tabulate();
	(*os) << "/ operator" << endl;
	level++;
	tabulate();
	(*os) << " (left)" << endl;
	root->left->Accept(this);
	tabulate();
	(*os) << " (right)" << endl;
	root->right->Accept(this);
	level--;
}

#pragma endregion






























