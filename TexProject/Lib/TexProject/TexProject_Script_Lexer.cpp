#include "TexProject_Script_Lexer.h"


#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace TexProject
{
	// utility functions;
	const string digitToChar(int digit)
	{
		switch (digit)
		{
		case 0: return "0";
		case 1: return "1";
		case 2: return "2";
		case 3: return "3";
		case 4: return "4";
		case 5: return "5";
		case 6: return "6";
		case 7: return "7";
		case 8: return "8";
		case 9: return "9";

		default: throw exception("Error! Integer is not a digit");
		}
	}

	const string intToString(int number)
	{
		string resStr = "";

		while (number != 0)
		{
			resStr = digitToChar(number % 10) + resStr;
			number /= 10;
		}

		if (resStr == "")
			return "0";

		return resStr;
	}



	//struct State definition;
	State::State(const string& name, const bool isAccepting) :
	name_(name),
	isAccepting_(isAccepting)
	{
	}

	State::State(State&& st) :
	name_(move(st.name_)),
	isAccepting_(st.isAccepting_)
	{
		//cout << "State::move-ctor\n";
	}

	State& State::operator=(const State& st)
	{
		if (&st != this)
		{
			this->name_ = st.name_;
			this->isAccepting_ = st.isAccepting_;
		}

		return *this;
	}

	State& State::operator=(State&& st)
	{
		if (&st != this)
		{
			this->name_ = move(st.name_);
			this->isAccepting_ = st.isAccepting_;

			//cout << "State::move-assign\n";
		}
		return *this;
	}

	bool State::operator<(const State& other) const
	{
		return this->name_ < other.name_;
	}

	ostream& operator<<(ostream& os, const State& st)
	{
		return os << st.name_ << "\t is accepting - " << boolalpha << st.isAccepting_;
	}



	//struct MoveFunctionArgument definition;
	MoveFunctionArgument::MoveFunctionArgument(const string& fromStateName, const char inputSymbol) :
	fromStateName_(fromStateName),
	inputSymbol_(inputSymbol)
	{
	}

	MoveFunctionArgument::MoveFunctionArgument(MoveFunctionArgument&& mfa) :
	fromStateName_(move(mfa.fromStateName_)),
	inputSymbol_(mfa.inputSymbol_)
	{
		//cout << "MoveFunctionArgument::move-ctor\n";
	}

	MoveFunctionArgument& MoveFunctionArgument::operator = (MoveFunctionArgument&& mfa)
	{
		if (this != &mfa)
		{
			this->fromStateName_ = move(mfa.fromStateName_);
			this->inputSymbol_ = move(mfa.inputSymbol_);

			//cout << "MoveFunctionArgument::move-assign\n";
		}

		return *this;
	}

	bool MoveFunctionArgument::operator<(const MoveFunctionArgument& mfa) const
	{
		bool areNotEqual = this->fromStateName_ != mfa.fromStateName_;

		if (areNotEqual)
			return this->fromStateName_ < mfa.fromStateName_;
		else
			return this->inputSymbol_ < mfa.inputSymbol_;

	}



	//struct IncomingHalfTransition definition;
	IncomingHalfTransition::IncomingHalfTransition(const string& toStateName) :
	toStateName_(toStateName)
	{
	}

	IncomingHalfTransition::IncomingHalfTransition(IncomingHalfTransition&& iht) :
	toStateName_(move(iht.toStateName_))
	{
		//cout << "IncomingHalfTransition::move-ctor\n";
	}

	IncomingHalfTransition& IncomingHalfTransition::operator = (IncomingHalfTransition&& iht)
	{
		if (this != &iht)
		{
			this->toStateName_ = move(iht.toStateName_);

			//cout << "IncomingHalfTransition::move-assing\n";
		}

		return *this;
	}



	// struct OutcomingHalfTransition definition;
	OutcomingHalfTransition::OutcomingHalfTransition(const string& fromStateName, const char inputSymbol) :
	fromStateName_(fromStateName),
	inputSymbol_(inputSymbol)
	{
	}

	OutcomingHalfTransition::OutcomingHalfTransition(OutcomingHalfTransition&& oht) :
	fromStateName_(move(oht.fromStateName_)),
	inputSymbol_(oht.inputSymbol_)
	{
		//cout << "OutcomingHalfTransition::move-ctor\n";
	}

	OutcomingHalfTransition& OutcomingHalfTransition::operator = (OutcomingHalfTransition&& oht)
	{
		if (this != &oht)
		{
			this->fromStateName_ = move(oht.fromStateName_);
			this->inputSymbol_ = oht.inputSymbol_;

			//cout << "OutcomingHalfTransition::move-assing\n";
		}

		return *this;
	}



	// struct MarkableStateName definition;
	MarkableStateName::MarkableStateName(const string& stateName, const bool isMarked) :
	stateName_(stateName),
	isMarked_(isMarked)
	{
	}

	bool MarkableStateName::operator<(const MarkableStateName& msn) const
	{
		return this->stateName_ < msn.stateName_;
	}



	// class StateNamesGenerator definition;
	const string StateNamesGenerator::digitToChar(int digit)
	{
		switch (digit)
		{
		case 0: return "0";
		case 1: return "1";
		case 2: return "2";
		case 3: return "3";
		case 4: return "4";
		case 5: return "5";
		case 6: return "6";
		case 7: return "7";
		case 8: return "8";
		case 9: return "9";
		default: return "\0";
		}
	}

	const string StateNamesGenerator::intToString(int i)
	{
		string resStr = "";

		while (i != 0)
		{
			resStr = digitToChar(i % 10) + resStr;
			i /= 10;
		}

		if (resStr == "")
			return "0";

		return resStr;
	}

	StateNamesGenerator::StateNamesGenerator() :
	counter_(0)
	{
	}

	const string StateNamesGenerator::getNextAvailableName()
	{
		return intToString(counter_++);
	}



	// class Token definition;
	Token::Token(const Type tokenType) :
	tokenType_(tokenType)
	{
	}

	const Token::Type Token::getTokenType() const
	{
		return tokenType_;
	}

	const string Token::getTokenTypeString() const
	{
		switch (tokenType_)
		{
		case Type::Keyword:			return "Keyword";
		case Type::Identifier:		return "Identifier";
		case Type::IntegerLiteral:	return "IntegerLiteral";
		case Type::RealLiteral:		return "RealLiteral";
		case Type::Operator:		return "Operator";
		default:					throw exception("Unexpected token type!");
		}
	}

	Token::~Token()
	{
	}

	Token* Token::createToken(const Type tokenType, const string& valueStr)
	{
		switch (tokenType)
		{
		case Type::Keyword:			return (Token*)new KeywordToken(Type::Keyword, valueStr);
		case Type::Identifier:		return (Token*)new IdentifierToken(Type::Identifier, valueStr);
		case Type::IntegerLiteral:	return (Token*)new IntegerLiteralToken(Type::IntegerLiteral, valueStr);
		case Type::RealLiteral:		return (Token*)new RealLiteralToken(Type::RealLiteral, valueStr);
		case Type::Operator:		return (Token*)new OperatorToken(Type::Operator, valueStr);
		default:					throw exception("Unexpected token type");
			break;
		}

		//if (tokenString == "Keyword")			return (Token*)new KeywordToken(Type::Keyword, valueStr);
		//if (tokenString == "Identifier")		return (Token*)new IdentifierToken(Type::Identifier, valueStr);
		//if (tokenString == "IntegerLiteral")	return (Token*)new IntegerLiteralToken(Type::IntegerLiteral, valueStr);
		//if (tokenString == "RealLiteral")		return (Token*)new RealLiteralToken(Type::RealLiteral, valueStr);
		//if (tokenString == "Operator")			return (Token*)new OperatorToken(Type::Operator, valueStr);
		//
		//throw exception("Unexpected token type");
	}

	Token::Type Token::getTypeByString(const std::string& tokenString)
	{
		if (tokenString == "Keyword")			return Type::Keyword;
		if (tokenString == "Identifier")		return Type::Identifier;
		if (tokenString == "IntegerLiteral")	return Type::IntegerLiteral;
		if (tokenString == "RealLiteral")		return Type::RealLiteral;
		if (tokenString == "Operator")			return Type::Operator;

		throw exception("Unexpected token type");
	}



	// class KeywordToken definitions;
	KeywordToken::KeywordToken(const Type tokenType, const std::string valueStr) :
	Token(tokenType),
	value_(valueStr)
	{
	}

	const string& KeywordToken::getValue() const
	{
		return value_;
	}



	// class IdentifierToken definitions;
	IdentifierToken::IdentifierToken(const Type tokenType, const std::string valueStr) :
	Token(tokenType),
	value_(valueStr)
	{
	}

	const string& IdentifierToken::getValue() const
	{
		return value_;
	}



	// class IntegerLiteralToken definitions;
	IntegerLiteralToken::IntegerLiteralToken(const Type tokenType, const std::string valueStr) :
	Token(tokenType),
	value_(atoi(valueStr.c_str()))
	{
	}

	const int IntegerLiteralToken::getValue() const
	{
		return value_;
	}


	// class RealLiteralToken definitions;
	RealLiteralToken::RealLiteralToken(const Type tokenType, const std::string valueStr) :
	Token(tokenType),
	value_(stof(valueStr.c_str()))
	{
	}

	const float RealLiteralToken::getValue() const
	{
		return value_;
	}



	// class OperatorTokendefinitions;
	OperatorToken::OperatorToken(const Type tokenType, const std::string valueStr) :
	Token(tokenType),
	value_(valueStr)
	{
	}

	const string& OperatorToken::getValue() const
	{
		return value_;
	}



	// class LexicalErrorException definition;
	LexicalErrorException::LexicalErrorException(const char* msg) :
	exception(msg)
	{
	}


	// class FiniteAutomaton definition;
	FiniteAutomaton::FiniteAutomaton() :
	states_(),
	initStateName_(),
	stateNameAcceptingTokens_()
	{
	}

	FiniteAutomaton::FiniteAutomaton(const FiniteAutomaton& fa) :
	states_(fa.states_),
	initStateName_(fa.initStateName_),
	stateNameAcceptingTokens_(fa.stateNameAcceptingTokens_)
	{
	}

	FiniteAutomaton::FiniteAutomaton(FiniteAutomaton&& fa) :
	states_(move(fa.states_)),
	initStateName_(move(fa.initStateName_)),
	stateNameAcceptingTokens_(move(fa.stateNameAcceptingTokens_))
	{
		//cout << "FiniteAutomaton::move-ctor\n";
	}

	bool FiniteAutomaton::isStateAccepting(const std::string& stateName) const
	{
		return (find_if(this->states_.begin(), this->states_.end(),
			[&stateName](const State& st)
		{
			return st.isAccepting_ && st.name_ == stateName;
		}) != this->states_.end());
	}

	FiniteAutomaton::~FiniteAutomaton()
	{
	}

	FiniteAutomaton& FiniteAutomaton::operator = (FiniteAutomaton&& fa)
	{
		if (this != &fa)
		{
			this->states_ = move(fa.states_);
			this->initStateName_ = move(fa.initStateName_);
			this->stateNameAcceptingTokens_ = move(fa.stateNameAcceptingTokens_);

			//cout << "FiniteAutomaton::move-assign\n";
		}
		return *this;
	}

	FiniteAutomaton& FiniteAutomaton::operator = (const FiniteAutomaton& fa)
	{
		if (this != &fa)
		{
			this->states_ = fa.states_;
			this->initStateName_ = fa.initStateName_;
			this->stateNameAcceptingTokens_ = fa.stateNameAcceptingTokens_;
		}
		return *this;
	}

	void FiniteAutomaton::serialize(ostream& os) const
	{
		/* File format:
		first line:		non-accepting state names;
		second line:	accepting state names (<state name> <accepting token value>);
		third line:		initial state name;

		further lines: transitions (<from-state name> <input symbol> <to-state name>);
		*/

		for_each(this->states_.begin(), this->states_.end(),
			[&os](const State& state)
		{
			if (!state.isAccepting_)
			{
				os << state.name_ << ' ';
			}
		});
		os << '\n';

		for_each(this->states_.begin(), this->states_.end(),
			[&os, this](const State& state)
		{
			if (state.isAccepting_)
			{
				os << state.name_ << ' ' << (int)this->stateNameAcceptingTokens_.at(state.name_) << '\t';
			}
		});
		os << '\n';

		os << this->initStateName_ << '\n';
	}

	void FiniteAutomaton::deserialize(istream& is)
	{
		/* File format:
		first line:		non-accepting state names;
		second line:	accepting state names (<state name> <accepting token value>);
		third line:		initial state name;

		further lines: transitions (<from-state name> <input symbol> <to-state name>);
		*/

		this->states_.clear();
		this->initStateName_.clear();
		this->stateNameAcceptingTokens_.clear();

		string line = "";
		getline(is, line);

		// reading non-accepting state names;
		istringstream myStream(line);
		copy(istream_iterator<string>(myStream), istream_iterator<string>(), inserter(this->states_, this->states_.begin()));

		getline(is, line);

		myStream.clear();
		myStream.str(line);

		// reading accepting state names;
		string stateName = "";
		int tokenTypeValue = 0;

		while (!myStream.eof())
		{
			myStream >> stateName >> tokenTypeValue;

			this->states_.insert(State(stateName, true));
			this->stateNameAcceptingTokens_[stateName] = (Token::Type)tokenTypeValue;
		}

		// reading initial state name;
		is >> this->initStateName_;
	}

	istream& operator>>(istream& is, FiniteAutomaton& fa)
	{
		string line = "";
		string titleString = "";

		// reading non-accepting states;
		getline(is, line);
		istringstream myStream(line);

		myStream >> titleString;

		string stateName = "";
		while (myStream >> stateName)
		{
			fa.states_.insert(State(stateName));
		}

		// reading accepting states;
		getline(is, line);
		myStream.clear();
		myStream.str(line);
		myStream.seekg(0, is.beg);

		myStream >> titleString;

		while (myStream >> stateName)
		{
			fa.states_.insert(State(stateName, true));
		}

		// reading initial state;
		is >> titleString;
		is >> stateName;
		fa.initStateName_ = stateName;

		return is;
	}

	ostream& operator<<(std::ostream& os, const FiniteAutomaton& fa)
	{
		os << "NFA Fragment:" << '\n';

		os << "   States: \n";
		copy(fa.states_.begin(), fa.states_.end(), ostream_iterator<State>(os, "\n"));

		os << "   Initial state name: " << fa.initStateName_ << '\n';

		return os;
	}



	// class DFA definition;
	DFA::DFA() :
	FiniteAutomaton(),
	transitions_()
	{
	}

	DFA::DFA(DFA&& dfa) :
	FiniteAutomaton(dfa),
	transitions_(move(dfa.transitions_))
	{
		//cout << "DFA::move-ctor\n";
	}

	bool DFA::acceptsString(const string& inputString) const
	{
		string currStateName = this->initStateName_;
		MoveFunctionArgument arg;

		for each (auto inputSymbol in inputString)
		{
			arg.fromStateName_ = currStateName;
			arg.inputSymbol_ = inputSymbol;

			try
			{
				currStateName = this->transitions_.at(arg);
			}
			catch (out_of_range ex)
			{
				return false;
			}
		}

		auto iter = find_if(this->states_.begin(), this->states_.end(), [&currStateName](const State& st)
		{
			return st.name_ == currStateName;
		});

		if (iter != this->states_.end())
			return iter->isAccepting_;
		else
			throw exception("Current state is not present in state alphabet!");
	}

	vector<Token*> DFA::tokenize(const std::string& inputString) const
	{
		vector<Token*> tokens;

		istringstream allCodeStream(inputString);
		string lineOfCode = "";

		for (int lineNumber = 1; getline(allCodeStream, lineOfCode, '\n'); ++lineNumber)
		{
			istringstream lineOfCodeStream(lineOfCode);
			string currReadStr = "";

			while (lineOfCodeStream >> currReadStr)
			{
				const string* lastAcceptingStateName = nullptr;
				const string* currStateName = &this->initStateName_;
				int currTokenLength = 0;
				int charsAfterlastAccepting = 0;
				int startPos = 0;

				MoveFunctionArgument arg;
				for (int i = 0; i < currReadStr.length(); ++i)
				{
					arg.fromStateName_ = *currStateName;
					arg.inputSymbol_ = currReadStr[i];

					try
					{
						currStateName = &this->transitions_.at(arg);

						bool isCurrStateAccepting = any_of(this->states_.begin(), this->states_.end(),
							[&currStateName](const State& st)
						{
							return st.isAccepting_ && st.name_ == *currStateName;
						});

						if (isCurrStateAccepting)
						{
							lastAcceptingStateName = currStateName;
							charsAfterlastAccepting = 0;
						}
						else
						{
							++charsAfterlastAccepting;
						}

						++currTokenLength;
					}
					catch (out_of_range ex)
					{
						if (lastAcceptingStateName == nullptr)
						{
							string message = "LINE " + intToString(lineNumber) + " \t-\t "
								+ " Lexical error: word \"" + currReadStr.substr(startPos, currReadStr.length()) + "\"";
							throw exception(message.c_str());
						}

						int realTokenLen = currTokenLength - charsAfterlastAccepting;
						tokens.push_back(Token::createToken(this->stateNameAcceptingTokens_.at(*lastAcceptingStateName), currReadStr.substr(startPos, realTokenLen)));

						startPos = startPos + realTokenLen;
						currTokenLength = 0;

						i -= (charsAfterlastAccepting + 1);

						lastAcceptingStateName = nullptr;
						currStateName = &this->initStateName_;
					}

					if (i == (currReadStr.length() - 1))
					{
						if (lastAcceptingStateName == nullptr)
						{
							string message = "LINE " + intToString(lineNumber) + " \t-\t "
								+ " Lexical error: word \"" + currReadStr.substr(startPos, currReadStr.length()) + "\"";
							throw LexicalErrorException(message.c_str());
						}

						int realTokenLen = currTokenLength - charsAfterlastAccepting;
						tokens.push_back(Token::createToken(this->stateNameAcceptingTokens_.at(*lastAcceptingStateName), currReadStr.substr(startPos, realTokenLen)));

						break;
					}
				}
			}
		}
		return tokens;
	}

	DFA& DFA::operator=(DFA&& dfa)
	{
		if (this != &dfa)
		{
			this->FiniteAutomaton::operator=(dfa);
			this->transitions_ = move(dfa.transitions_);

			//cout << "DFA::move-assign\n";
		}

		return *this;
	}



	void DFA::serialize(ostream& os) const
	{
		/* File format:
		first line:		non-accepting state names;
		second line:	accepting state names (<state name> <accepting token value>);
		third line:		initial state name;

		further lines: transitions (<from-state name> <input symbol> <to-state name>);
		*/

		FiniteAutomaton::serialize(os);

		for (auto transition : this->transitions_)
		{
			os << transition.first.fromStateName_ << ' ' << transition.first.inputSymbol_ << ' ' << transition.second << '\n';
		}
	}

	void DFA::deserialize(istream& is)
	{
		/* File format:
		first line:		non-accepting state names;
		second line:	accepting state names (<state name> <accepting token value>);
		third line:		initial state name;

		further lines: transitions (<from-state name> <input symbol> <to-state name>);
		*/

		this->transitions_.clear();

		FiniteAutomaton::deserialize(is);

		// reading transitions;
		string fromStateName = "";
		char inputSymbool = '\0';
		string toStateName = "";

		while (!is.eof())
		{
			is >> fromStateName >> inputSymbool >> toStateName;
			this->transitions_[MoveFunctionArgument(fromStateName, inputSymbool)] = toStateName;
		}
	}



	ostream& operator<<(ostream& os, const DFA& dfa)
	{
		os << *(FiniteAutomaton*)(&dfa);

		os << "   Transitions: \n";
		for each (auto elem in dfa.transitions_)
		{
			os << elem.first.fromStateName_ << ' ' << elem.first.inputSymbol_ << "  ->  " << elem.second;
			os << '\n';
		}

		return os;
	}

	istream& operator>>(istream& is, DFA& dfa)
	{
		is >> *(FiniteAutomaton*)(&dfa);

		string line = "";
		string titleString = "";
		string stateName = "";

		// reading transitions;
		map <MoveFunctionArgument, string> transitions;

		is >> titleString;
		getline(is, line);

		istringstream myStream;

		while (getline(is, line))
		{
			myStream.clear();
			myStream.str(line);
			myStream.seekg(0, is.beg);

			string fromStateName = "";
			myStream >> fromStateName;

			char inputSymbol = '\0';
			myStream >> inputSymbol;

			myStream >> titleString;

			string toStateName;
			myStream >> toStateName;

			transitions[MoveFunctionArgument(fromStateName, inputSymbol)] = toStateName;
		}

		dfa.transitions_ = transitions;

		return is;
	}



	// class NFA definition;
	StateNamesGenerator NFAFragment::nfaStateNamesGen_ = StateNamesGenerator();
	StateNamesGenerator NFAFragment::dfaStateNamesGen_ = StateNamesGenerator();

	// primitives creation functions;
	NFAFragment NFAFragment::createNFAForEpsilon()
	{
		return NFAFragment::createNFAForSingleSymbol('#');
	}

	NFAFragment NFAFragment::createNFAForSingleSymbol(const char symbol)
	{
		NFAFragment resFrag;

		string stateName = nfaStateNamesGen_.getNextAvailableName();

		resFrag.states_.insert(State(stateName));
		resFrag.initStateName_ = stateName;

		resFrag.incomingHalfTrans_ = IncomingHalfTransition(stateName);
		resFrag.outcomingHalfTrans_ = OutcomingHalfTransition(stateName, symbol);

		return resFrag;
	}

	NFAFragment NFAFragment::createNFAForString(const string& str)
	{
		vector <NFAFragment> singleSymbolFrags;
		for_each(str.begin(), str.end(), [&singleSymbolFrags](const char symbol)
		{
			singleSymbolFrags.push_back(NFAFragment::createNFAForSingleSymbol(symbol));
		});

		auto beginIter = singleSymbolFrags.begin();

		NFAFragment result = *(beginIter++);

		for_each(beginIter, singleSymbolFrags.end(), [&result](const NFAFragment& frag)
		{
			result.makeConcatenation(frag);
		});

		//return NFAFragment::makeConcatenation(singleSymbolFrags);

		return result;
	}

	NFAFragment NFAFragment::createNFAForRange(const char first, const char last)
	{
		NFAFragment result;

		result.states_.insert(nfaStateNamesGen_.getNextAvailableName());
		result.states_.insert(nfaStateNamesGen_.getNextAvailableName());

		const State* firstState = &*result.states_.begin();
		const State* secondState = &*result.states_.rbegin();

		result.initStateName_ = firstState->name_;

		for (int i = first; i <= last; ++i)
		{
			result.transitions_[MoveFunctionArgument(firstState->name_, i)]
				.insert(secondState->name_);
		}

		result.incomingHalfTrans_.toStateName_ = firstState->name_;

		result.outcomingHalfTrans_.fromStateName_ = secondState->name_;
		result.outcomingHalfTrans_.inputSymbol_ = '#';

		return result;
	}

	NFAFragment NFAFragment::createNFAForRange(const std::vector<char>& symbols)
	{
		NFAFragment result;

		result.states_.insert(nfaStateNamesGen_.getNextAvailableName());
		result.states_.insert(nfaStateNamesGen_.getNextAvailableName());

		const State* firstState = &*result.states_.begin();
		const State* secondState = &*result.states_.rbegin();

		result.initStateName_ = firstState->name_;

		for_each(symbols.begin(), symbols.end(), [&result, &firstState, &secondState](const char symb)
		{
			result.transitions_[MoveFunctionArgument(firstState->name_, symb)]
				.insert(secondState->name_);
		});

		result.incomingHalfTrans_.toStateName_ = firstState->name_;

		result.outcomingHalfTrans_.fromStateName_ = secondState->name_;
		result.outcomingHalfTrans_.inputSymbol_ = '#';

		return result;
	}



	// compositional functions;
	NFAFragment NFAFragment::makeParallel(vector<NFAFragment> fragments)
	{
		if (fragments.empty())
			return NFAFragment();

		NFAFragment result = NFAFragment::createNFAForEpsilon();
		NFAFragment ending = NFAFragment::createNFAForEpsilon();

		for_each(fragments.begin(), fragments.end(), [&result, &ending](NFAFragment& frag)
		{
			// midle - end;
			frag.states_.insert(ending.states_.begin(), ending.states_.end());

			frag.transitions_.insert(ending.transitions_.begin(), ending.transitions_.end());
			frag.transitions_[MoveFunctionArgument(frag.outcomingHalfTrans_.fromStateName_, frag.outcomingHalfTrans_.inputSymbol_)]
				.insert(ending.incomingHalfTrans_.toStateName_);

			frag.outcomingHalfTrans_ = ending.outcomingHalfTrans_;

			// begin - midle;
			result.states_.insert(frag.states_.begin(), frag.states_.end());
			//
			result.stateNameAcceptingTokens_.insert(frag.stateNameAcceptingTokens_.begin(), frag.stateNameAcceptingTokens_.end());
			//

			result.transitions_.insert(frag.transitions_.begin(), frag.transitions_.end());
			result.transitions_[MoveFunctionArgument(result.outcomingHalfTrans_.fromStateName_, result.outcomingHalfTrans_.inputSymbol_)]
				.insert(frag.incomingHalfTrans_.toStateName_);
		});

		result.outcomingHalfTrans_ = ending.outcomingHalfTrans_;

		return result;
	}



	// methods for converting NFA -> DFA;
	const string NFAFragment::getEpsilonClosure(const string& stateName) const
	{
		set<MarkableStateName> resSet;
		istringstream myStr(stateName);
		copy(istream_iterator<string>(myStr), istream_iterator<string>(), inserter(resSet, resSet.begin()));

		auto msnIter = find_if(resSet.begin(), resSet.end(), [](const MarkableStateName& m) { return m.isMarked_ == false; });
		while (msnIter != resSet.end())
		{
			try
			{
				//isStateAccepting = isStateAccepting || any_of(this->states_.begin(), this->states_.end(), [&msnIter](const State& st)
				//{
				//	return (st.name_ == msnIter->stateName_) && st.isAccepting_;
				//});

				const set<string>& aSet = this->transitions_.at(MoveFunctionArgument(msnIter->stateName_, '#'));
				resSet.insert(aSet.begin(), aSet.end());
			}
			catch (out_of_range&)
			{
			}

			msnIter._Ptr->_Myval.isMarked_ = true;
			msnIter = (find_if(resSet.begin(), resSet.end(), [](const MarkableStateName& m) { return m.isMarked_ == false; }));
		}


		string resStateName = "";
		for_each(resSet.begin(), resSet.end(), [&resStateName](const MarkableStateName& m)
		{
			resStateName += (' ' + m.stateName_);
		});

		return resStateName;
	}

	const string NFAFragment::getReachableThroughS(const std::string& stateName, const char S) const
	{
		set<MarkableStateName> markableStates;
		istringstream myStr(stateName);
		copy(istream_iterator<string>(myStr), istream_iterator<string>(), inserter(markableStates, markableStates.begin()));

		string resString = "";

		auto msnIter = find_if(markableStates.begin(), markableStates.end(), [](const MarkableStateName& m) { return m.isMarked_ == false; });
		while (msnIter != markableStates.end())
		{
			try
			{
				const set<string>& aSet = this->transitions_.at(MoveFunctionArgument(msnIter->stateName_, S));
				for_each(aSet.begin(), aSet.end(), [&resString](const string& str)
				{
					resString += (' ' + str);
				});
			}
			catch (out_of_range&)
			{
			}

			msnIter._Ptr->_Myval.isMarked_ = true;
			msnIter = (find_if(markableStates.begin(), markableStates.end(), [](const MarkableStateName& m) { return m.isMarked_ == false; }));
		}

		return resString;
	}

	const set<char> NFAFragment::getExternalAlphabet() const
	{
		NfaDfaStatesMap nfaDfaStatesMap;

		set<char> externAlpha;
		for (auto& elem : this->transitions_)
		{
			char symbol = elem.first.inputSymbol_;
			if (symbol != '#')
			{
				externAlpha.insert(symbol);
			}
		}

		return move(externAlpha);
	}

	NFAFragment::NFAFragment() :
	FiniteAutomaton(),
	incomingHalfTrans_(),
	outcomingHalfTrans_(),
	transitions_()
	{
	}

	NFAFragment::NFAFragment(const NFAFragment& frag) :
	FiniteAutomaton(frag),
	incomingHalfTrans_(frag.incomingHalfTrans_),
	outcomingHalfTrans_(frag.outcomingHalfTrans_),
	transitions_(frag.transitions_)
	{
	}


	NFAFragment::NFAFragment(NFAFragment&& frag) :
	FiniteAutomaton(frag),
	incomingHalfTrans_(move(frag.incomingHalfTrans_)),
	outcomingHalfTrans_(move(frag.outcomingHalfTrans_)),
	transitions_(move(frag.transitions_))
	{
		//cout << "NFAFragment::move-ctor\n";
	}



	const DFA NFAFragment::convertToDFA() const
	{
		set<char> externAlpha = this->getExternalAlphabet();

		DFA resultDfa;

		string initDfaStateFullName = this->getEpsilonClosure({ this->initStateName_ });

		istringstream myStr(initDfaStateFullName);
		string currStateName = "";
		int maxPriority = 0;

		while (myStr >> currStateName)
		{
			int currPriority = 0;
			if (this->isStateAccepting(currStateName) &&
				(currPriority = (int)this->stateNameAcceptingTokens_.at(currStateName)) > maxPriority)
			{
				maxPriority = currPriority;
			}
		}

		string shortDfaStateName = dfaStateNamesGen_.getNextAvailableName();

		if (maxPriority > 0)
		{
			resultDfa.states_.insert(State(shortDfaStateName, true));
			resultDfa.stateNameAcceptingTokens_[shortDfaStateName] = (Token::Type)maxPriority;
		}
		else
		{
			resultDfa.states_.insert(State(shortDfaStateName, false));
		}

		NfaDfaStatesMap nfaDfaStatesMap;
		nfaDfaStatesMap[initDfaStateFullName] = shortDfaStateName;

		resultDfa.initStateName_ = shortDfaStateName;

		set<MarkableStateName> markableDfaStateFullNames;
		markableDfaStateFullNames.insert(initDfaStateFullName);

		auto msn = find_if(markableDfaStateFullNames.begin(), markableDfaStateFullNames.end(),
			[](const MarkableStateName& m) { return m.isMarked_ == false; });

		while (msn != markableDfaStateFullNames.end())
		{
			for (const char& symbol : externAlpha)
			{
				string reachableThroughS = this->getReachableThroughS(msn->stateName_, symbol);
				string newDfaStateFullName = this->getEpsilonClosure(reachableThroughS);

				if (newDfaStateFullName != "")
				{
					istringstream myNewStr(newDfaStateFullName);
					currStateName = "";
					maxPriority = 0;

					while (myNewStr >> currStateName)
					{
						int currPriority = 0;
						if (this->isStateAccepting(currStateName) &&
							(currPriority = (int)this->stateNameAcceptingTokens_.at(currStateName)) > maxPriority)
						{
							maxPriority = currPriority;
						}
					}


					if (nfaDfaStatesMap.find(newDfaStateFullName) == nfaDfaStatesMap.end())
					{
						shortDfaStateName = dfaStateNamesGen_.getNextAvailableName();
						if (maxPriority > 0)
						{
							resultDfa.states_.insert(State(shortDfaStateName, true));
							resultDfa.stateNameAcceptingTokens_[shortDfaStateName] = (Token::Type)maxPriority;
						}
						else
						{
							resultDfa.states_.insert(State(shortDfaStateName, false));
						}

						nfaDfaStatesMap[newDfaStateFullName] = shortDfaStateName;
						markableDfaStateFullNames.insert(newDfaStateFullName);
					}
					else
					{
						shortDfaStateName = nfaDfaStatesMap.at(newDfaStateFullName);
					}

					try
					{
						string existingStateName = resultDfa.transitions_.at(MoveFunctionArgument(nfaDfaStatesMap[msn->stateName_], symbol));
						if (this->isStateAccepting(nfaDfaStatesMap[newDfaStateFullName]) && (int)resultDfa.stateNameAcceptingTokens_.at(existingStateName) < (int)resultDfa.stateNameAcceptingTokens_.at(nfaDfaStatesMap[newDfaStateFullName]))
						{
							resultDfa.transitions_[MoveFunctionArgument(nfaDfaStatesMap[msn->stateName_], symbol)] = nfaDfaStatesMap[newDfaStateFullName];
						}
					}
					catch (out_of_range ex)
					{
						resultDfa.transitions_[MoveFunctionArgument(nfaDfaStatesMap[msn->stateName_], symbol)] = nfaDfaStatesMap[newDfaStateFullName];
					}
				}
			}
			// ----------;
			msn._Ptr->_Myval.isMarked_ = true;
			msn = find_if(markableDfaStateFullNames.begin(), markableDfaStateFullNames.end(),
				[](const MarkableStateName& m) { return m.isMarked_ == false; });
		}

		return resultDfa; //~
	}





	// compositional modifying methods
	NFAFragment& NFAFragment::makeConcatenation(const NFAFragment& fragment)
	{
		this->states_.insert(fragment.states_.begin(), fragment.states_.end());
		//
		this->stateNameAcceptingTokens_.insert(fragment.stateNameAcceptingTokens_.begin(), fragment.stateNameAcceptingTokens_.end());
		//
		this->transitions_.insert(fragment.transitions_.begin(), fragment.transitions_.end());

		this->transitions_[MoveFunctionArgument(this->outcomingHalfTrans_.fromStateName_, this->outcomingHalfTrans_.inputSymbol_)]
			.insert(fragment.incomingHalfTrans_.toStateName_);

		this->outcomingHalfTrans_ = fragment.outcomingHalfTrans_;

		return *this;
	}

	NFAFragment& NFAFragment::makeStar()
	{
		//NFAFragment epsFrag = NFAFragment::createNFAForEpsilon();

		State newState(nfaStateNamesGen_.getNextAvailableName());

		this->states_.insert(newState);

		this->transitions_[MoveFunctionArgument(newState.name_, '#')]
			.insert(this->incomingHalfTrans_.toStateName_);
		this->transitions_[MoveFunctionArgument(this->outcomingHalfTrans_.fromStateName_, this->outcomingHalfTrans_.inputSymbol_)]
			.insert(newState.name_);

		this->initStateName_ = newState.name_;

		this->incomingHalfTrans_.toStateName_ = newState.name_;

		this->outcomingHalfTrans_.fromStateName_ = newState.name_;
		this->outcomingHalfTrans_.inputSymbol_ = '#';

		return *this;
	}

	NFAFragment& NFAFragment::makePlus()
	{
		State leftNewState = State(nfaStateNamesGen_.getNextAvailableName());
		State rightNewState = State(nfaStateNamesGen_.getNextAvailableName());

		this->states_.insert(leftNewState);
		this->states_.insert(rightNewState);

		this->transitions_[MoveFunctionArgument(leftNewState.name_, '#')]
			.insert(this->incomingHalfTrans_.toStateName_);
		this->transitions_[MoveFunctionArgument(this->outcomingHalfTrans_.fromStateName_, this->outcomingHalfTrans_.inputSymbol_)]
			.insert(rightNewState.name_);
		this->transitions_[MoveFunctionArgument(rightNewState.name_, '#')]
			.insert(leftNewState.name_);

		this->initStateName_ = leftNewState.name_;

		this->incomingHalfTrans_.toStateName_ = leftNewState.name_;

		this->outcomingHalfTrans_.fromStateName_ = rightNewState.name_;
		this->outcomingHalfTrans_.inputSymbol_ = '#';

		return *this;
	}

	NFAFragment& NFAFragment::makeQuestionMark()
	{
		this->transitions_[MoveFunctionArgument(this->incomingHalfTrans_.toStateName_, '#')]
			.insert(this->outcomingHalfTrans_.fromStateName_);

		return *this;
	}

	NFAFragment& NFAFragment::addAcceptingState(const Token::Type acceptingTokenType)
	{
		string stateName = nfaStateNamesGen_.getNextAvailableName();
		State acceptingState(stateName, true);
		this->stateNameAcceptingTokens_[stateName] = acceptingTokenType; // !!!;

		this->states_.insert(acceptingState);
		this->transitions_[MoveFunctionArgument(this->outcomingHalfTrans_.fromStateName_, this->outcomingHalfTrans_.inputSymbol_)]
			.insert(acceptingState.name_);

		this->outcomingHalfTrans_.fromStateName_ = acceptingState.name_;
		this->outcomingHalfTrans_.inputSymbol_ = '#'; // ??!!;

		return *this;
	}

	NFAFragment& NFAFragment::operator = (NFAFragment&& frag)
	{
		if (this != &frag)
		{
			this->FiniteAutomaton::operator=(frag);
			this->incomingHalfTrans_ = move(frag.incomingHalfTrans_);
			this->outcomingHalfTrans_ = move(frag.outcomingHalfTrans_);
			this->transitions_ = move(frag.transitions_);

			//cout << "NFAFragment::move-assign\n";
		}

		return *this;
	}



	// reading / writing;
	ostream& operator<<(ostream& os, const NFAFragment& nfaFrag)
	{
		os << *(FiniteAutomaton*)(&nfaFrag);

		os << "   Incoming half-transition:\n"
			<< "To-state - " << nfaFrag.incomingHalfTrans_.toStateName_ << '\n';

		os << "   Outcoming half-transition:\n"
			<< "From-state - " << nfaFrag.outcomingHalfTrans_.fromStateName_ << '\n'
			<< "Input symbol - " << nfaFrag.outcomingHalfTrans_.inputSymbol_ << '\n';

		os << "   Transitions: \n";
		for each (auto elem in nfaFrag.transitions_)
		{
			os << elem.first.fromStateName_ << ' ' << elem.first.inputSymbol_ << "  ->  ";
			copy(elem.second.begin(), elem.second.end(), ostream_iterator<string>(os, " "));
			os << '\n';
		}

		return os;
	}

	istream& operator>>(istream& is, NFAFragment& nfaFrag)
	{
		is >> *(FiniteAutomaton*)(&nfaFrag);

		string line = "";
		string titleString = "";
		string stateName = "";

		// reading incoming half-transition;
		is >> titleString;
		is >> stateName;
		nfaFrag.incomingHalfTrans_ = IncomingHalfTransition(stateName);

		// reading outcoming half-transition;
		is >> titleString;
		is >> stateName;
		char inputSymbol;
		is >> inputSymbol;
		nfaFrag.outcomingHalfTrans_ = OutcomingHalfTransition(stateName, inputSymbol);


		// reading transitions;
		map <MoveFunctionArgument, set<string> > transitions;

		is >> titleString;
		getline(is, line);

		istringstream myStream;

		while (getline(is, line))
		{
			myStream.clear();
			myStream.str(line);
			myStream.seekg(0, is.beg);

			string fromStateName = "";
			myStream >> fromStateName;

			char inputSymbol = '\0';
			myStream >> inputSymbol;

			myStream >> titleString;

			set<string> toStateNames;
			while (myStream >> stateName)
			{
				toStateNames.insert(stateName);
			}

			transitions[MoveFunctionArgument(fromStateName, inputSymbol)] = toStateNames;
		}

		nfaFrag.transitions_ = transitions;

		return is;
	}


	// class Lexer definition;
	Lexer::Lexer() :
	dfa_()
	{
		vector<NFAFragment> allFrags;

		// for keywords;
		/*
		if
		and
		or
		else
		struct
		*/
		allFrags.push_back(NFAFragment::createNFAForString("if").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("else").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("and").addAcceptingState(Token::Type::Operator)); // operator!
		allFrags.push_back(NFAFragment::createNFAForString("or").addAcceptingState(Token::Type::Operator)); // operator!
		allFrags.push_back(NFAFragment::createNFAForString("not").addAcceptingState(Token::Type::Operator)); // operator!
		allFrags.push_back(NFAFragment::createNFAForString("struct").addAcceptingState(Token::Type::Keyword));

		/*type idendifiers*/
		allFrags.push_back(NFAFragment::createNFAForString("bool").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("int").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("uint").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("float").addAcceptingState(Token::Type::Keyword));

		allFrags.push_back(NFAFragment::createNFAForString("vec2").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("vec3").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("vec4").addAcceptingState(Token::Type::Keyword));

		allFrags.push_back(NFAFragment::createNFAForString("ivec2").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("ivec3").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("ivec4").addAcceptingState(Token::Type::Keyword));

		allFrags.push_back(NFAFragment::createNFAForString("mat2").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("mat3").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("mat4").addAcceptingState(Token::Type::Keyword));

		allFrags.push_back(NFAFragment::createNFAForString("quat").addAcceptingState(Token::Type::Keyword));

		/*1D, 2D, 3D, Cube*/
		allFrags.push_back(NFAFragment::createNFAForString("1D").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("2D").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("3D").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("Cube").addAcceptingState(Token::Type::Keyword));

		/*in, out, extern*/
		allFrags.push_back(NFAFragment::createNFAForString("in").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("out").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("extern").addAcceptingState(Token::Type::Keyword));

		/*true, false*/
		allFrags.push_back(NFAFragment::createNFAForString("true").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("false").addAcceptingState(Token::Type::Keyword));

		/*rgba*/
		allFrags.push_back(NFAFragment::createNFAForString("red").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("green").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("blue").addAcceptingState(Token::Type::Keyword));
		allFrags.push_back(NFAFragment::createNFAForString("alpha").addAcceptingState(Token::Type::Keyword));


		// for identifiers;
		// [_a-zA-Z][_a-zA-z0-9]*
		NFAFragment nfaForaToz = NFAFragment::createNFAForRange('a', 'z');
		NFAFragment nfaForAToZ = NFAFragment::createNFAForRange('A', 'Z');
		NFAFragment nfaFor0To9 = NFAFragment::createNFAForRange('0', '9');
		NFAFragment nfaForUnderscore = NFAFragment::createNFAForSingleSymbol('_');

		NFAFragment nfaForIDs =
			NFAFragment::makeParallel({ nfaForaToz, nfaForAToZ, nfaForUnderscore })
			.makeConcatenation(
			NFAFragment::makeParallel({ nfaForaToz, nfaForAToZ, nfaForUnderscore, nfaFor0To9 }).makeStar()
			)
			.addAcceptingState(Token::Type::Identifier);

		allFrags.push_back(nfaForIDs);



		// for integer literals;
		// [+-]?[0-9]+
		//NFAFragment nfaForIntegerLiteral =
		//	NFAFragment::createNFAForRange({ '+', '-' })
		//	.makeQuestionMark()
		//	.makeConcatenation(NFAFragment::createNFAForRange('0', '9')
		//	.makePlus())
		//	.addAcceptingState(Token::Type::IntegerLiteral);
		//
		//allFrags.push_back(nfaForIntegerLiteral);

		// for integer literals;
		// [0-9]+
		NFAFragment nfaForIntegerLiteral =
			NFAFragment::createNFAForRange('0', '9')
			.makePlus()
			.addAcceptingState(Token::Type::IntegerLiteral);

		allFrags.push_back(nfaForIntegerLiteral);


		// nfa for real literal;
		// [+-]?([0-9]+.[0-9]*|.[0-9]+)	
		//NFAFragment nfaForPlusMinus = 
		//	NFAFragment::createNFAForRange({ '+', '-' })
		//	.makeQuestionMark();
		//
		//NFAFragment nfaForfirstForm =
		//	NFAFragment::createNFAForRange('0', '9')
		//	.makePlus()
		//	.makeConcatenation(NFAFragment::createNFAForSingleSymbol('.'))
		//	.makeConcatenation(NFAFragment::createNFAForRange('0', '9').makeStar());
		//
		//NFAFragment nfaForSecondForm =
		//	NFAFragment::createNFAForSingleSymbol('.')
		//	.makeConcatenation(NFAFragment::createNFAForRange('0', '9').makePlus());
		//
		//NFAFragment nfaForRealLiteral =
		//	nfaForPlusMinus
		//	.makeConcatenation(NFAFragment::makeParallel({ nfaForfirstForm, nfaForSecondForm }))
		//	.addAcceptingState(Token::Type::RealLiteral);

		// nfa for real literal;
		// ([0-9]+.[0-9]*|.[0-9]+)	
		NFAFragment nfaForfirstForm =
			NFAFragment::createNFAForRange('0', '9')
			.makePlus()
			.makeConcatenation(NFAFragment::createNFAForSingleSymbol('.'))
			.makeConcatenation(NFAFragment::createNFAForRange('0', '9').makeStar());

		NFAFragment nfaForSecondForm =
			NFAFragment::createNFAForSingleSymbol('.')
			.makeConcatenation(NFAFragment::createNFAForRange('0', '9').makePlus());

		NFAFragment nfaForRealLiteral =
			NFAFragment::makeParallel({ nfaForfirstForm, nfaForSecondForm })
			.addAcceptingState(Token::Type::RealLiteral);

		allFrags.push_back(nfaForRealLiteral);


		// for operators;

		/*arithmetical operators
		+
		-
		*
		/
		*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('+').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('-').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('*').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('/').addAcceptingState(Token::Type::Operator));

		/*logical operators
		<
		>
		==
		!=
		&&
		||
		!
		*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('<').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('>').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForString("==").addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForString("!=").addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForString("&&").addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForString("||").addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('!').addAcceptingState(Token::Type::Operator));

		/*assignment*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('=').addAcceptingState(Token::Type::Operator));

		/*semicolon*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol(';').addAcceptingState(Token::Type::Operator));

		/*dot*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('.').addAcceptingState(Token::Type::Operator));

		/*brackets*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('(').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol(')').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('[').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol(']').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('{').addAcceptingState(Token::Type::Operator));
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol('}').addAcceptingState(Token::Type::Operator));

		/*comma*/
		allFrags.push_back(NFAFragment::createNFAForSingleSymbol(',').addAcceptingState(Token::Type::Operator));

		this->dfa_ = NFAFragment::makeParallel(allFrags).convertToDFA();


		// serialization;
		ofstream outputFile("Serialized result DFA.txt");

		this->dfa_.serialize(outputFile);
	}

	Lexer::Lexer(const string& fileName) :
	dfa_()
	{
		ifstream inputFile(fileName);
		if (!inputFile)
		{
			string message = "Cannot open file \"" + fileName + "\"";
			throw exception(message.c_str());
		}

		this->dfa_.deserialize(inputFile);
	}

	vector<Token*> Lexer::tokenize(const string& inputString) const
	{
		return this->dfa_.tokenize(inputString);
	}

	Lexer::~Lexer()
	{
	}
}
