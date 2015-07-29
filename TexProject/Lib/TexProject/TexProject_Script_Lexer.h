#pragma once
#include <TexProject/TexProject_Header.h>

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>


namespace TexProject
{
	/*Utility functions*/
	const std::string digitToChar(int digit);
	const std::string intToString(int number);
	
	
	/*Utility classes and structs for finite automata structure and algorithms*/
	struct State;
	struct MoveFunctionArgument;
	struct IncomingHalfTransition;
	struct OutcomingHalfTransition;
	struct MarkableStateName;
	class StateNamesGenerator;
	

	/*Token classes*/
	class Token;
	class KeywordToken;
	class IdentifierToken;
	class IntegerLiteralToken;
	class RealLiteralToken;
	class OperatorToken;
	
	
	/*Lexical error exception class*/
	class LexicalErrorException;

	
	/*Finite automaton classes*/
	class FiniteAutomaton;
	class DFA;
	class NFAFragment;


	/*Lexer class*/
	class Lexer;











	// Finite automaton state;
	struct State
	{
		std::string name_;
		bool isAccepting_;

		State(const std::string& name = "", const bool isAccepting = false);
		State(State&& st);

		bool operator<(const State& other) const;

		State& operator=(const State& st);
		State& operator=(State&& st);

		friend std::ostream& operator<<(std::ostream& os, const State& st);
	};



	// Key in map of transitions;
	struct MoveFunctionArgument
	{
		std::string fromStateName_;
		char inputSymbol_;

		MoveFunctionArgument(const std::string& fromStateName = "", const char inputSymbol = '\0');
		MoveFunctionArgument(MoveFunctionArgument&& mfa);


		MoveFunctionArgument& operator=(MoveFunctionArgument&& mfa);

		bool operator<(const MoveFunctionArgument& mfa) const;
	};



	// Half-transition structs;

	struct IncomingHalfTransition
	{
		std::string toStateName_;

		IncomingHalfTransition(const std::string& toStateName = "");
		IncomingHalfTransition(IncomingHalfTransition&& iht);

		IncomingHalfTransition& operator=(IncomingHalfTransition&& iht);
	};



	struct OutcomingHalfTransition
	{
		std::string fromStateName_;
		char inputSymbol_;

		OutcomingHalfTransition(const std::string& fromStateName = "", const char inputSymbol = '\0');
		OutcomingHalfTransition(OutcomingHalfTransition&& oht);

		OutcomingHalfTransition& operator=(OutcomingHalfTransition&& oht);
	};



	// For generating unique state names (significant for NFA's combinators and generators);
	class StateNamesGenerator
	{
		// statics;
	private:
		static const std::string digitToChar(int digit);
		static const std::string intToString(int i);

	private:
		int counter_;

	public:
		StateNamesGenerator();

		const std::string getNextAvailableName();
	};



	struct MarkableStateName
	{
		std::string stateName_;
		bool isMarked_;

		MarkableStateName(const std::string& stateName = "", const bool isMarked = false);

		bool operator<(const MarkableStateName& msn) const;
	};



	class Token
	{
	public:
		enum class Type // priority!;
		{
			None = 0,
			Keyword = 5,
			Identifier = 4,
			IntegerLiteral = 3,
			RealLiteral = 2,
			Operator = 1
		};

	private:
		Type tokenType_;

	public:
		Token(const Type tokenType);

		const Type getTokenType() const;
		const std::string getTokenTypeString() const;

		virtual ~Token() = 0;

		// statics:
		static Token* createToken(const Type tokenType, const std::string& valueStr);
		static Type getTypeByString(const std::string& tokenString);
	};



	class KeywordToken
		:Token
	{
		friend class Token;

		std::string value_;
		KeywordToken(const Type tokenType, const std::string valueStr);

	public:
		const std::string& getValue() const;
	};



	class IdentifierToken
		:Token
	{
		friend class Token;

		std::string value_;
		IdentifierToken(const Type tokenType, const std::string valueStr);

	public:
		const std::string& getValue() const;
	};



	class IntegerLiteralToken
		:Token
	{
		friend class Token;

		int value_;
		IntegerLiteralToken(const Type tokenType, const std::string valueStr);

	public:
		const int getValue() const;
	};



	class RealLiteralToken
		:Token
	{
		friend class Token;

		float value_;
		RealLiteralToken(const Type tokenType, const std::string valueStr);

	public:
		const float getValue() const;
	};



	class OperatorToken
		:Token
	{
		friend class Token;

		std::string value_;
		OperatorToken(const Type tokenType, const std::string valueStr);

	public:
		const std::string& getValue() const;
	};



	class LexicalErrorException
		:public std::exception
	{
	public:
		LexicalErrorException(const char* msg);
	};



	class FiniteAutomaton
	{
	protected:
		// convention: # - epsilon;
		std::set<State> states_;
		std::string initStateName_;

		std::map<std::string, Token::Type> stateNameAcceptingTokens_;

	public:
		FiniteAutomaton();
		FiniteAutomaton(const FiniteAutomaton& fa);
		FiniteAutomaton(FiniteAutomaton&& fa);

		bool isStateAccepting(const std::string& stateName) const;

		virtual ~FiniteAutomaton() = 0;

		FiniteAutomaton& operator=(FiniteAutomaton&& fa);
		FiniteAutomaton& operator=(const FiniteAutomaton& fa);


		virtual void serialize(std::ostream& os) const;
		virtual void deserialize(std::istream& is);

		friend std::istream& operator>>(std::istream& is, FiniteAutomaton& fa);
		friend std::ostream& operator<<(std::ostream& os, const FiniteAutomaton& fa);
	};



	class DFA
		:public FiniteAutomaton
	{
		friend class NFAFragment;

		std::map<MoveFunctionArgument, std::string> transitions_;

	public:
		DFA();
		DFA(DFA&& dfa);

		bool acceptsString(const std::string& inputString) const;

		std::vector<Token*> tokenize(const std::string& inputString) const;

		DFA& operator=(DFA&& dfa);

		virtual void serialize(std::ostream& os) const override;
		virtual void deserialize(std::istream& is) override;

		friend std::ostream& operator<<(std::ostream& os, const DFA& dfa);
		friend std::istream& operator>>(std::istream& is, DFA& dfa);
	};



	class NFAFragment
		:public FiniteAutomaton
	{
		// static members;
	private:
		static StateNamesGenerator nfaStateNamesGen_;
		static StateNamesGenerator dfaStateNamesGen_;

	public:
		static NFAFragment createNFAForEpsilon();
		static NFAFragment createNFAForSingleSymbol(const char symbol);
		static NFAFragment createNFAForString(const std::string& str);
		static NFAFragment createNFAForRange(const char first, const char last); // [first, last];
		static NFAFragment createNFAForRange(const std::vector<char>& symbols);

		static NFAFragment makeParallel(std::vector<NFAFragment> frags);


	private:
		IncomingHalfTransition incomingHalfTrans_;
		OutcomingHalfTransition outcomingHalfTrans_;
		std::map<MoveFunctionArgument, std::set<std::string> > transitions_;

	private:
		typedef std::map<std::string, std::string> NfaDfaStatesMap;

		const std::string getEpsilonClosure(const std::string& stateName/*, DfaNfaStatesMap& dfaNfaStatesMap*/) const;
		const std::string getReachableThroughS(const std::string& stateName, const char S/*, DfaNfaStatesMap& dfaNfaStatesMap*/) const;
		const std::set<char> getExternalAlphabet() const;

	public:

		NFAFragment();
		NFAFragment(const NFAFragment& frag);
		NFAFragment(NFAFragment&& frag);

		const DFA convertToDFA() const;

		// compositional modifying methods;
		NFAFragment& makeConcatenation(const NFAFragment& fragment); // +
		// makeParallel - static;
		NFAFragment& makeStar(); // +
		NFAFragment& makePlus(); // +
		NFAFragment& makeQuestionMark();
		NFAFragment& addAcceptingState(const Token::Type acceptingTokenType); // +

		NFAFragment& operator=(NFAFragment&& frag);

		friend std::ostream& operator<<(std::ostream& os, const NFAFragment& nfaFrag);
		friend std::istream& operator>>(std::istream& is, NFAFragment& nfaFrag);
	};



	class Lexer
	{
	private:
		DFA dfa_;

	public:
		Lexer();
		Lexer(const std::string& fileName);

		std::vector<Token*> tokenize(const std::string& inputString) const;

		~Lexer();
	};

}