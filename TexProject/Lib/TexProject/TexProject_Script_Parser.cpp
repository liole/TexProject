#include "TexProject_Script_Parser.h"
using namespace TexProject;


#include <TexProject/TexProject_Script_Translator.h>


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































