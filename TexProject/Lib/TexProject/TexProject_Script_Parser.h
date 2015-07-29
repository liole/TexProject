#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Textures.h>


#include <vector>


namespace TexProject
{
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
				namespace Binary
				{
					struct Assignment;
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
			Statement
		};

		virtual ~Instruction() = default;

		virtual Instruction::Type				GetInstructionType() const = 0;
		virtual void							Accept(Translator* translator);
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
					Texture1D,Texture2D,Texture3D,TextureCube
				};

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
				};
			}
			namespace Operators
			{
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
					};
				}
			}
		}
	}


	struct Parser
	{
	};
}




















