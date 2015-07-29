#include "TexProject_Script_Translator.h"
using namespace TexProject;


void					Translator::translate(Instruction* root)
{
}
void					Translator::translate(Instructions::Block* root)
{
	uint32 localStack = stack;

	for(auto i: root->content)
	{
		operation = Operation::None;
		i->Accept(this);
	}

	localStack = stack - localStack;
	if(localStack)
	{
		code->push_back(ASM86::LEA_ESP_LOC_ESPP32[0]);
		code->push_back(ASM86::LEA_ESP_LOC_ESPP32[1]);
		code->push_back(ASM86::LEA_ESP_LOC_ESPP32[2]);
		code->push_back(ASM86::val1(&localStack));
		code->push_back(ASM86::val2(&localStack));
		code->push_back(ASM86::val3(&localStack));
		code->push_back(ASM86::val4(&localStack));
	}
}
void					Translator::translate(Instructions::Definition* root)
{
	if(root->storage->IsLocal())
	{
		auto var = (Instructions::Expressions::Storages::Variable*)root->storage;

		if(root->initializer)
		{
			operation = Operation::InitializationVariable;
			operationType = var->type;
			root->initializer->Accept(this);

			switch(var->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				stack += 4;
				var->offset = stack;
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				stack += 16;
				var->offset = stack;
			}
			break;
			}
		}
		else
		{
			switch(var->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::PUSH_EAX);
				stack += 4;
				var->offset = stack;
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::SUB_ESP8[0]);
				code->push_back(ASM86::SUB_ESP8[1]);
				code->push_back(0x10);
				stack += 16;
				var->offset = stack;
			}
			break;
			}
		}
	}
}
void					Translator::translate(Instructions::Expression* root)
{
}
void					Translator::translate(Instructions::Expressions::Operator* root)
{
}
void					Translator::translate(Instructions::Expressions::Operators::Binary::Assignment* root)
{
	auto oldOperation = operation;
	auto oldOperationType = operationType;

	if(operation == Operation::Assignation)
	{
		root->left->Accept(this);
	}
	else
	{
		if(root->right->GetExpressionType() == Instructions::Expression::Type::Storage)
		{
			operation = Operation::Receiving;
			root->left->Accept(this); // location of variable in eax

			operation = Operation::Assignation;
			operationType = root->left->type;
			root->right->Accept(this);
		}
		else
		{
			operation = Operation::None;
			root->right->Accept(this);

			operation = Operation::Receiving;
			root->left->Accept(this);

			operation = Operation::Assignation;
			operationType = root->left->type;
			root->right->Accept(this);
		}
	}
	/*auto oldOperation = operation;
	auto oldOperationType = operationType;

	if(oldOperation == Operation::Assignation)
	{
		code->push_back(ASM86::PUSH_EAX);
	}

	//if(root->right->GetExpressionType() == Instructions::Expression::Type::Storage)
	{
		operation = Operation::Receiving;
		root->left->Accept(this); // location of variable in eax

		operation = Operation::Assignation;
		operationType = root->left->type;
		root->right->Accept(this);
	}

	if(oldOperation == Operation::Assignation)
	{
		code->push_back(ASM86::POP_EAX);

		operation = oldOperation;
		operationType = oldOperationType;
		root->left->Accept(this);
	}*/
}
void					Translator::translate(Instructions::Expressions::Storage* root)
{
}
void					Translator::translate(Instructions::Expressions::Storages::Literal* root)
{
	switch(operation)
	{
	case Translator::Operation::InitializationVariable:
	{
		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1((uint8*)root->value + 0x00));
				code->push_back(ASM86::val2((uint8*)root->value + 0x00));
				code->push_back(ASM86::val3((uint8*)root->value + 0x00));
				code->push_back(ASM86::val4((uint8*)root->value + 0x00));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1((uint8*)root->value + 0x04));
				code->push_back(ASM86::val2((uint8*)root->value + 0x04));
				code->push_back(ASM86::val3((uint8*)root->value + 0x04));
				code->push_back(ASM86::val4((uint8*)root->value + 0x04));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1((uint8*)root->value + 0x08));
				code->push_back(ASM86::val2((uint8*)root->value + 0x08));
				code->push_back(ASM86::val3((uint8*)root->value + 0x08));
				code->push_back(ASM86::val4((uint8*)root->value + 0x08));
				code->push_back(ASM86::PUSH32);
				code->push_back(ASM86::val1((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val2((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val3((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val4((uint8*)root->value + 0x0C));
			}
			break;
			}
		}
		break;
		}
	}
	break;
	case Translator::Operation::Assignation:
	{
		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::MOV_LOC_EAX[0]);
				code->push_back(ASM86::MOV_LOC_EAX[1]);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::MOV_LOC_EAX[0]);
				code->push_back(ASM86::MOV_LOC_EAX[1]);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x04);
				code->push_back(ASM86::val1((uint8*)root->value + 0x04));
				code->push_back(ASM86::val2((uint8*)root->value + 0x04));
				code->push_back(ASM86::val3((uint8*)root->value + 0x04));
				code->push_back(ASM86::val4((uint8*)root->value + 0x04));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x08);
				code->push_back(ASM86::val1((uint8*)root->value + 0x08));
				code->push_back(ASM86::val2((uint8*)root->value + 0x08));
				code->push_back(ASM86::val3((uint8*)root->value + 0x08));
				code->push_back(ASM86::val4((uint8*)root->value + 0x08));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x0C);
				code->push_back(ASM86::val1((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val2((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val3((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val4((uint8*)root->value + 0x0C));
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Texture2D:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::MOV_LOC_EAX[0]);
				code->push_back(ASM86::MOV_LOC_EAX[1]);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x04);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x08);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x0C);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::MOV_LOC_EAX[0]);
				code->push_back(ASM86::MOV_LOC_EAX[1]);
				code->push_back(ASM86::val1(root->value));
				code->push_back(ASM86::val2(root->value));
				code->push_back(ASM86::val3(root->value));
				code->push_back(ASM86::val4(root->value));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x04);
				code->push_back(ASM86::val1((uint8*)root->value + 0x04));
				code->push_back(ASM86::val2((uint8*)root->value + 0x04));
				code->push_back(ASM86::val3((uint8*)root->value + 0x04));
				code->push_back(ASM86::val4((uint8*)root->value + 0x04));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x08);
				code->push_back(ASM86::val1((uint8*)root->value + 0x08));
				code->push_back(ASM86::val2((uint8*)root->value + 0x08));
				code->push_back(ASM86::val3((uint8*)root->value + 0x08));
				code->push_back(ASM86::val4((uint8*)root->value + 0x08));

				code->push_back(ASM86::MOV_LOC_EAXP8[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8[1]);
				code->push_back(0x0C);
				code->push_back(ASM86::val1((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val2((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val3((uint8*)root->value + 0x0C));
				code->push_back(ASM86::val4((uint8*)root->value + 0x0C));
			}
			break;
			}
		}
		break;
		}
	}
	break;
	}
}
void					Translator::translate(Instructions::Expressions::Storages::Variable* root)
{
	switch(operation)
	{
	case Translator::Operation::InitializationVariable:
	{
		auto off = stack - root->offset;

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				if(off > 0)
				{
					code->push_back(ASM86::PUSH_LOC_ESPP32[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP32[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP32[2]);
					code->push_back(ASM86::val1(&off));
					code->push_back(ASM86::val2(&off));
					code->push_back(ASM86::val3(&off));
					code->push_back(ASM86::val4(&off));
				}
				else
				{
					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);
				}
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				if(off > 0)
				{
					code->push_back(ASM86::PUSH_LOC_ESPP32[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP32[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP32[2]);
					code->push_back(ASM86::val1(&off));
					code->push_back(ASM86::val2(&off));
					code->push_back(ASM86::val3(&off));
					code->push_back(ASM86::val4(&off));

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);
				}
				else
				{
					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);

					code->push_back(ASM86::PUSH_LOC_ESP[0]);
					code->push_back(ASM86::PUSH_LOC_ESP[1]);
					code->push_back(ASM86::PUSH_LOC_ESP[2]);
				}
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				if(off > 0)
				{
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[0]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[1]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[2]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[3]);
					code->push_back(ASM86::val1(&off));
					code->push_back(ASM86::val2(&off));
					code->push_back(ASM86::val3(&off));
					code->push_back(ASM86::val4(&off));


					code->push_back(ASM86::SUB_ESP8[0]);
					code->push_back(ASM86::SUB_ESP8[1]);
					code->push_back(0x10);

					off += 16;
					code->push_back(ASM86::MOVUPS_ESP_XMM0[0]);
					code->push_back(ASM86::MOVUPS_ESP_XMM0[1]);
					code->push_back(ASM86::MOVUPS_ESP_XMM0[2]);
					code->push_back(ASM86::MOVUPS_ESP_XMM0[3]);
				}
				else
				{
					code->push_back(ASM86::PUSH_LOC_ESPP8[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[2]);
					code->push_back(0x10);
					code->push_back(ASM86::PUSH_LOC_ESPP8[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[2]);
					code->push_back(0x10);
					code->push_back(ASM86::PUSH_LOC_ESPP8[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[2]);
					code->push_back(0x10);
					code->push_back(ASM86::PUSH_LOC_ESPP8[0]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[1]);
					code->push_back(ASM86::PUSH_LOC_ESPP8[2]);
					code->push_back(0x10);
				}
			}
			break;
			}
		}
		break;
		}
	}
	break;
	case Translator::Operation::Receiving:
	{
		code->push_back(ASM86::MOV_EAX_ESP[0]);
		code->push_back(ASM86::MOV_EAX_ESP[1]);

		auto off = stack - root->offset;

		if(off > 0)
		{
			code->push_back(ASM86::ADD_EAX);
			code->push_back(ASM86::val1(&off));
			code->push_back(ASM86::val2(&off));
			code->push_back(ASM86::val3(&off));
			code->push_back(ASM86::val4(&off));
		}
	}
	break;
	case Translator::Operation::Assignation:
	{
		auto off = stack - root->offset;

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				if(off > 0)
				{
					code->push_back(ASM86::MOV_EDX_LOC_ESPP32[0]);
					code->push_back(ASM86::MOV_EDX_LOC_ESPP32[1]);
					code->push_back(ASM86::MOV_EDX_LOC_ESPP32[2]);
					code->push_back(ASM86::val1(&off));
					code->push_back(ASM86::val2(&off));
					code->push_back(ASM86::val3(&off));
					code->push_back(ASM86::val4(&off));
				}
				else
				{
					code->push_back(ASM86::MOV_EDX_LOC_ESP[0]);
					code->push_back(ASM86::MOV_EDX_LOC_ESP[1]);
					code->push_back(ASM86::MOV_EDX_LOC_ESP[2]);
				}

				code->push_back(ASM86::MOV_LOC_EAX_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAX_EDX[1]);
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				if(off > 0)
				{
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[0]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[1]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[2]);
					code->push_back(ASM86::MOVUPS_XMM0_ESPP32[3]);
					code->push_back(ASM86::val1(&off));
					code->push_back(ASM86::val2(&off));
					code->push_back(ASM86::val3(&off));
					code->push_back(ASM86::val4(&off));
				}
				else
				{
					code->push_back(ASM86::MOVUPS_XMM0_ESP[0]);
					code->push_back(ASM86::MOVUPS_XMM0_ESP[1]);
					code->push_back(ASM86::MOVUPS_XMM0_ESP[2]);
					code->push_back(ASM86::MOVUPS_XMM0_ESP[3]);
				}

				code->push_back(ASM86::MOVUPS_EAX_XMM0[0]);
				code->push_back(ASM86::MOVUPS_EAX_XMM0[1]);
				code->push_back(ASM86::MOVUPS_EAX_XMM0[2]);
			}
			break;
			}
		}
		break;
		}
	}
	break;
	}
}
void					Translator::translate(Instructions::Expressions::Storages::In* root)
{
	switch(operation)
	{
	case Translator::Operation::InitializationVariable:
	{
		code->push_back(ASM86::MOV_EDX);
		code->push_back(ASM86::val1(root->location));
		code->push_back(ASM86::val2(root->location));
		code->push_back(ASM86::val3(root->location));
		code->push_back(ASM86::val4(root->location));

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::PUSH_LOC_EDX[0]);
				code->push_back(ASM86::PUSH_LOC_EDX[1]);
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::PUSH_LOC_EDX[0]);
				code->push_back(ASM86::PUSH_LOC_EDX[1]);
				code->push_back(ASM86::PUSH_LOC_EDX[0]);
				code->push_back(ASM86::PUSH_LOC_EDX[1]);
				code->push_back(ASM86::PUSH_LOC_EDX[0]);
				code->push_back(ASM86::PUSH_LOC_EDX[1]);
				code->push_back(ASM86::PUSH_LOC_EDX[0]);
				code->push_back(ASM86::PUSH_LOC_EDX[1]);
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::MOVUPS_XMM0_EDX[0]);
				code->push_back(ASM86::MOVUPS_XMM0_EDX[1]);
				code->push_back(ASM86::MOVUPS_XMM0_EDX[2]);

				code->push_back(ASM86::SUB_ESP8[0]);
				code->push_back(ASM86::SUB_ESP8[1]);
				code->push_back(0x10);

				code->push_back(ASM86::MOVUPS_ESP_XMM0[0]);
				code->push_back(ASM86::MOVUPS_ESP_XMM0[1]);
				code->push_back(ASM86::MOVUPS_ESP_XMM0[2]);
				code->push_back(ASM86::MOVUPS_ESP_XMM0[3]);
			}
			break;
			}
		}
		break;
		}
	}
	break;
	case Translator::Operation::Assignation:
	{
		code->push_back(ASM86::MOV_EDX);
		code->push_back(ASM86::val1(root->location));
		code->push_back(ASM86::val2(root->location));
		code->push_back(ASM86::val3(root->location));
		code->push_back(ASM86::val4(root->location));

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Float:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::MOV_EDX_LOC_EDX[0]);
				code->push_back(ASM86::MOV_EDX_LOC_EDX[1]);

				code->push_back(ASM86::MOV_LOC_EAX_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAX_EDX[1]);
			}
			break;
			}
		}
		break;
		case Instructions::Expressions::Storage::Type::Texture2D:
		{
			switch(root->type)
			{
			case Instructions::Expressions::Storage::Type::Float:
			{
				code->push_back(ASM86::MOV_EDX_LOC_EDX[0]);
				code->push_back(ASM86::MOV_EDX_LOC_EDX[1]);

				code->push_back(ASM86::MOV_LOC_EAX_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAX_EDX[1]);

				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[1]);
				code->push_back(0x04);

				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[1]);
				code->push_back(0x08);

				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[0]);
				code->push_back(ASM86::MOV_LOC_EAXP8_EDX[1]);
				code->push_back(0x0C);
			}
			break;
			case Instructions::Expressions::Storage::Type::Vec4:
			{
				code->push_back(ASM86::MOVUPS_XMM0_EDX[0]);
				code->push_back(ASM86::MOVUPS_XMM0_EDX[1]);
				code->push_back(ASM86::MOVUPS_XMM0_EDX[2]);

				code->push_back(ASM86::MOVUPS_EAX_XMM0[0]);
				code->push_back(ASM86::MOVUPS_EAX_XMM0[1]);
				code->push_back(ASM86::MOVUPS_EAX_XMM0[2]);
			}
			break;
			}
		}
		break;
		}
	}
	break;
	}
}
void					Translator::translate(Instructions::Expressions::Storages::Out* root)
{
	switch(operation)
	{
	case Translator::Operation::InitializationVariable:
	{
		code->push_back(ASM86::MOV_EAX_LOC[0]);
		code->push_back(ASM86::loc1(root->location));
		code->push_back(ASM86::loc2(root->location));
		code->push_back(ASM86::loc3(root->location));
		code->push_back(ASM86::loc4(root->location));

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			code->push_back(ASM86::MOVUPS_XMM0_EAX[0]);
			code->push_back(ASM86::MOVUPS_XMM0_EAX[1]);
			code->push_back(ASM86::MOVUPS_XMM0_EAX[2]);

			code->push_back(ASM86::SUB_ESP8[0]);
			code->push_back(ASM86::SUB_ESP8[1]);
			code->push_back(0x10);

			code->push_back(ASM86::MOVUPS_ESP_XMM0[0]);
			code->push_back(ASM86::MOVUPS_ESP_XMM0[1]);
			code->push_back(ASM86::MOVUPS_ESP_XMM0[2]);
			code->push_back(ASM86::MOVUPS_ESP_XMM0[3]);
		}
		break;
		}
	}
	break;
	case Translator::Operation::Receiving:
	{
		code->push_back(ASM86::MOV_EAX);
		code->push_back(ASM86::loc1(root->location));
		code->push_back(ASM86::loc2(root->location));
		code->push_back(ASM86::loc3(root->location));
		code->push_back(ASM86::loc4(root->location));
		code->push_back(ASM86::MOV_EAX_LOC_EAX[0]);
		code->push_back(ASM86::MOV_EAX_LOC_EAX[1]);
	}
	break;
	case Translator::Operation::Assignation:
	{
		code->push_back(ASM86::MOV_EDX);
		code->push_back(ASM86::val1(root->location));
		code->push_back(ASM86::val2(root->location));
		code->push_back(ASM86::val3(root->location));
		code->push_back(ASM86::val4(root->location));

		switch(operationType)
		{
		case Instructions::Expressions::Storage::Type::Vec4:
		{
			code->push_back(ASM86::MOVUPS_XMM0_EDX[0]);
			code->push_back(ASM86::MOVUPS_XMM0_EDX[1]);
			code->push_back(ASM86::MOVUPS_XMM0_EDX[2]);

			code->push_back(ASM86::MOVUPS_EAX_XMM0[0]);
			code->push_back(ASM86::MOVUPS_EAX_XMM0[1]);
			code->push_back(ASM86::MOVUPS_EAX_XMM0[2]);
		}
		break;
		case Instructions::Expressions::Storage::Type::Texture2D:
		{
			code->push_back(ASM86::MOVUPS_XMM0_EDX[0]);
			code->push_back(ASM86::MOVUPS_XMM0_EDX[1]);
			code->push_back(ASM86::MOVUPS_XMM0_EDX[2]);

			code->push_back(ASM86::MOVUPS_EAX_XMM0[0]);
			code->push_back(ASM86::MOVUPS_EAX_XMM0[1]);
			code->push_back(ASM86::MOVUPS_EAX_XMM0[2]);
		}
		break;
		}
	}
	break;
	}
}

std::vector<uint8>		Translator::TranslateToASM86(Instruction* root)
{
	std::vector<uint8> code_;
	code = &code_;

	stack = 0;

	root->Accept(this);

	code = nullptr;
	return code_;
}































