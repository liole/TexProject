#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Textures.h>
#include "TexProject_Script_Lexer.h"


#include <string>
#include <vector>
#include <map>


namespace TexProject
{
	class Visitor;

	struct Instruction;
	namespace Instructions
	{
		struct Block;
		struct Definition;
		struct Expression;
		namespace Expressions
		{
			struct Storage;
			struct Operator;
			namespace Storages
			{
				struct Literal;
				struct Variable;
				struct Out;
				struct In;
			}
			namespace Operators
			{
				struct BinaryOperator;
				namespace Binary
				{
					struct Assignment;

					struct Plus;
					struct Minus;
					struct Multiply;
					struct Divide;
				}
			}
		}
	}


	struct Instruction
	{
		enum class Type
		{
			Block,
			Definition,
			Expression,
			Statement,
			Empty
		};

		virtual ~Instruction() = default;

		virtual Instruction::Type				GetInstructionType() const
		{
			return Type::Empty;
		}
		virtual void							Accept(Translator* translator);
		virtual void							Accept(Visitor* visitor);
	};
	namespace Instructions
	{
		struct Block;
		struct Definition;
		struct Expression;
		namespace Expressions
		{
			struct Storage;
			struct Operator;
		}

		struct Block:
			public Instruction
		{
			std::vector<Instruction*>				content;

			virtual Instruction::Type				GetInstructionType() const
			{
				return Instruction::Type::Block;
			}
			virtual void							Accept(Translator* translator);
			virtual void							Accept(Visitor* visitor);

			virtual ~Block();
		};
		struct Definition:
			public Instruction
		{
			Expressions::Storage*					storage = nullptr;
			Expression*								initializer = nullptr;

			inline Definition() = default;
			inline Definition(Expressions::Storage* storage_,Expression* initializer_):
				storage(storage_),initializer(initializer_)
			{
			}

			virtual Instruction::Type				GetInstructionType() const
			{
				return Instruction::Type::Definition;
			}
			virtual void							Accept(Translator* translator);
			virtual void							Accept(Visitor* visitor);
		
			virtual ~Definition();
		};
		struct Expression:
			public Instruction
		{
			enum class Type
			{
				Storage,
				Operator
			};

			virtual Expression::Type				GetExpressionType() const = 0;
			virtual Instruction::Type				GetInstructionType() const
			{
				return Instruction::Type::Expression;
			}
			virtual void							Accept(Translator* translator);
			virtual void							Accept(Visitor* visitor);
		};

		namespace Expressions
		{
			struct Storage:
				public Expression
			{
				struct External
				{
					void*							location = nullptr;

					inline External() = default;
					inline External(void* location_):
						location(location_)
					{
					}
				};

				enum class Type
				{
					Bool,Int,Float,
					Vec2,IVec2,
					Vec3,IVec3,
					Vec4,IVec4,
					Mat2,Mat3,Mat4,
					Texture1D,Texture2D,Texture3D,TextureCube,
					__size__
				};

				static std::string TypeNames[(unsigned int)Type::__size__];

				Type								type;

				inline Storage() = default;
				inline Storage(Type& type_):
					type(type_)
				{
				}

				inline Storage::Type				GetStorageType() const
				{
					return type;
				}
				virtual Expression::Type			GetExpressionType() const
				{
					return Expression::Type::Storage;
				}
				virtual void						Accept(Translator* translator);
				virtual void						Accept(Visitor* visitor);
				virtual bool						IsLocal() const
				{
					return false;
				}
			};

			struct Operator:
				public Expression
			{
				virtual Expression::Type			GetExpressionType() const
				{
					return Expression::Type::Operator;
				}
				virtual void						Accept(Translator* translator);
				virtual void						Accept(Visitor* visitor);
			};

			namespace Storages
			{
				struct Literal:
					public Storage
				{
					void*						value = nullptr;

					inline Literal() = default;
					inline Literal(Type type_,void* value_):
						Storage(type_),
						value(value_)
					{
					}

					virtual void				Accept(Translator* translator);
					virtual void				Accept(Visitor* visitor);

					virtual ~Literal();
				};
				struct Variable:
					public Storage
				{
					uint32						offset = 0;

					inline Variable() = default;
					inline Variable(Storage::Type type_):
						Storage(type_)
					{
					}

					virtual void				Accept(Translator* translator);
					virtual void				Accept(Visitor* visitor);
					virtual bool				IsLocal() const override
					{
						return true;
					}
				};
				struct Out:
					public Variable,
					public Storage::External
				{
					inline Out() = default;
					inline Out(Storage::Type type_,void* location_):
						Variable(type_),
						External(location_)
					{
					}

					virtual void				Accept(Translator* translator);
					virtual void				Accept(Visitor* visitor);
				};
				struct In:
					public Storage,
					public Storage::External
				{
					inline In() = default;
					inline In(Storage::Type type_,void* location_):
						Storage(type_),
						External(location_)
					{
					}

					virtual void				Accept(Translator* translator);
					virtual void				Accept(Visitor* visitor);
				};
			}
			namespace Operators
			{
				struct BinaryOperator :
					public Operator
				{
					Expression*				left = nullptr;
					Expression*				right = nullptr;

					inline BinaryOperator() = default;
					inline BinaryOperator(Expression* left_, Expression* right_) :
						Operator(),
						left(left_),
						right(right_)
					{
					}

					virtual int				priority() { return 0; }

					virtual void			Accept(Translator* translator);
					virtual void			Accept(Visitor* visitor);

					virtual ~BinaryOperator();
				};
				namespace Binary
				{
					struct Assignment:
						public Operator
					{
						Storages::Variable*		left = nullptr;
						Expression*				right = nullptr;

						inline Assignment() = default;
						inline Assignment(Storages::Variable* left_,Expression* right_):
							Operator(),
							left(left_),
							right(right_)
						{
						}

						virtual void			Accept(Translator* translator);
						virtual void			Accept(Visitor* visitor);

						virtual ~Assignment();
					};

					struct Plus :
						public BinaryOperator
					{
						inline Plus() = default;
						inline Plus(Expression* left_, Expression* right_) :
							BinaryOperator(left_, right_)
						{
						}

						virtual int				priority() { return 1; }

						virtual void			Accept(Translator* translator);
						virtual void			Accept(Visitor* visitor);
					};
					struct Minus :
						public BinaryOperator
					{
						inline Minus() = default;
						inline Minus(Expression* left_, Expression* right_) :
							BinaryOperator(left_, right_)
						{
						}

						virtual int				priority() { return 1; }

						virtual void			Accept(Translator* translator);
						virtual void			Accept(Visitor* visitor);
					};
					struct Multiply :
						public BinaryOperator
					{
						inline Multiply() = default;
						inline Multiply(Expression* left_, Expression* right_) :
							BinaryOperator(left_, right_)
						{
						}

						virtual int				priority() { return 2; }

						virtual void			Accept(Translator* translator);
						virtual void			Accept(Visitor* visitor);
					};
					struct Divide :
						public BinaryOperator
					{
						inline Divide() = default;
						inline Divide(Expression* left_, Expression* right_) :
							BinaryOperator(left_, right_)
						{
						}

						virtual int				priority() { return 2; }

						virtual void			Accept(Translator* translator);
						virtual void			Accept(Visitor* visitor);
					};
				}
			}
		}
	}

	using namespace Instructions;

	class ParserError
	{
		Token* token;
		string message;
	public:
		ParserError(Token* tkn, string msg) :
			token(tkn),
			message(msg)
		{}
		string what()
		{
			string tokenValue = "";
			switch (token->getTokenType())
			{
			case Token::Type::Keyword:			tokenValue = ((KeywordToken*)token)->getValue(); break;
			case Token::Type::Identifier:		tokenValue = ((IdentifierToken*)token)->getValue(); break;
			case Token::Type::IntegerLiteral:	tokenValue = std::to_string(((IntegerLiteralToken*)token)->getValue()); break;
			case Token::Type::RealLiteral:		tokenValue = std::to_string(((RealLiteralToken*)token)->getValue()); break;
			case Token::Type::Operator:			tokenValue = ((OperatorToken*)token)->getValue(); break;
			default:							throw std::exception("Unexpected token type\n");
				break;
			}
			return "Error in token '" + tokenValue + "'. " + message + ".";
		}
	};

	class Parser
	{
		std::vector<Token*> tokens;
		std::multimap <string, Expressions::Storage*> storages;

		typedef std::vector<Token*>::iterator TokenIter;
	public:
		Parser(std::vector<Token*> tkns);

		bool isOperator(TokenIter& iter);
		bool isOperator(TokenIter& iter, string op);
		bool isKeyword(TokenIter& iter);
		bool isKeyword(TokenIter& iter, string kw);
		bool isIdentifier(TokenIter& iter);
		string getIdentifier(TokenIter& iter);
		Expressions::Storage::Type* isTypeName(TokenIter& iter);
		Expressions::Storage* isStorage(TokenIter& iter);
		Expressions::Storages::Literal* isIntegerLiteral(TokenIter& iter);
		Expressions::Storages::Literal* isRealLiteral(TokenIter& iter);
		Expressions::Storages::Literal* isBoolLiteral(TokenIter& iter);
		Expressions::Storages::Literal* isVecMatLiteral(TokenIter& iter);
		Expressions::Storages::Literal* isLiteral(TokenIter& iter);
		Expressions::Operators::BinaryOperator* isBinaryOperator(TokenIter& iter);
		Block* isBlock(TokenIter& iter);
		Instruction* isInstruction(TokenIter& iter);
		bool isEmptyInstruction(TokenIter& iter);
		Definition* isDefinition(TokenIter& iter);
		Expressions::Operators::Binary::Assignment* isAssignment(TokenIter& iter);
		Expression* isExpression(TokenIter& iter);

		Block* parse();

		std::multimap <string, Expressions::Storage*>* getStorages();

		~Parser();
	};

	class Visitor
	{
	public:
		virtual void visit(Instruction* root) = 0;
		virtual void visit(Instructions::Block* root) = 0;
		virtual void visit(Instructions::Definition* root) = 0;
		virtual void visit(Instructions::Expression* root) = 0;
		virtual void visit(Instructions::Expressions::Operator* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::Binary::Assignment* root) = 0;
		virtual void visit(Instructions::Expressions::Storage* root) = 0;
		virtual void visit(Instructions::Expressions::Storages::Literal* root) = 0;
		virtual void visit(Instructions::Expressions::Storages::Variable* root) = 0;
		virtual void visit(Instructions::Expressions::Storages::In* root) = 0;
		virtual void visit(Instructions::Expressions::Storages::Out* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::BinaryOperator* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::Binary::Plus* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::Binary::Minus* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::Binary::Multiply* root) = 0;
		virtual void visit(Instructions::Expressions::Operators::Binary::Divide* root) = 0;
	};

	class TreeSerializer : public Visitor
	{
		int level;
		std::multimap <string, Instructions::Expressions::Storage*>* storages;
		std::ostream* os;
	public:
		TreeSerializer(std::multimap <string, Instructions::Expressions::Storage*>* _storages, std::ostream& _os);

		virtual void visit(Instruction* root);
		virtual void visit(Instructions::Block* root);
		virtual void visit(Instructions::Definition* root);
		virtual void visit(Instructions::Expression* root);
		virtual void visit(Instructions::Expressions::Operator* root);
		virtual void visit(Instructions::Expressions::Operators::Binary::Assignment* root);
		virtual void visit(Instructions::Expressions::Storage* root);
		virtual void visit(Instructions::Expressions::Storages::Literal* root);
		virtual void visit(Instructions::Expressions::Storages::Variable* root);
		virtual void visit(Instructions::Expressions::Storages::In* root);
		virtual void visit(Instructions::Expressions::Storages::Out* root);
		virtual void visit(Instructions::Expressions::Operators::BinaryOperator* root);
		virtual void visit(Instructions::Expressions::Operators::Binary::Plus* root);
		virtual void visit(Instructions::Expressions::Operators::Binary::Minus* root);
		virtual void visit(Instructions::Expressions::Operators::Binary::Multiply* root);
		virtual void visit(Instructions::Expressions::Operators::Binary::Divide* root);

		void tabulate();
	};

}




















