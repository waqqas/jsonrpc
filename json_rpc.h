#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <any>
#include <variant>

#include "JsonRpcParser.h"
#include "JsonRpcLexer.h"
#include "JsonRpcBaseVisitor.h"
#include "antlr4-runtime.h"

namespace jsonrpc
{
    using namespace antlr4;
    using namespace std;

    enum class msg_type
    {
        unknown,
        request,
        response,
        error
    };

    struct request
    {
        string method;
        any params;
    };

    struct response
    {
        any result;
    };

    struct error
    {
        int32_t code;
        string message;
    };

    struct message
    {
        msg_type type = msg_type::unknown;
        string version;
        int32_t id = -1;
        variant<request, response, error> data;
    };

    class parser
    {
        class visitor : public JsonRpcBaseVisitor
        {
            //     enum class state_type
            //     {
            //         header,
            //         params
            //     };

            //     state_type _state{state_type::header};

            // public:
            //     virtual antlrcpp::Any visitJson(JSONParser::JsonContext *ctx) override
            //     {
            //         return visitValue(ctx->value());
            //     }

            //     virtual antlrcpp::Any visitObj(JSONParser::ObjContext *ctx) override
            //     {
            //         message msg;
            //         size_t numChildren = ctx->children.size();
            //         for (size_t i = 0; i < numChildren; i++)
            //         {
            //             antlrcpp::Any childResult = ctx->children[i]->accept(this);
            //         }
            //         return msg;
            //     }

            //     virtual antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override
            //     {
            //         if (_state == state_type::header)
            //         {
            //             auto key = ctx->STRING()->getText();
            //             if (key == "jsonrpc")
            //             {
            //                 string version = ctx->value()->STRING()->getText();
            //             }
            //             else if (key == "method")
            //             {
            //                 // msg_type::request
            //             }
            //             else if (key == "result")
            //             {
            //                 // msg_type::response
            //             }
            //             else if (key == "error")
            //             {
            //                 // msg_type::error
            //             }
            //             else if (key == "params")
            //             {
            //                 _state = state_type::params;

            //                 visitValue(ctx->value());

            //                 _state = state_type::header;
            //             }
            //         }
            //         else if (_state == state_type::params)
            //         {
            //         }
            //         return visitChildren(ctx);
            //     }

            //     virtual antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override
            //     {
            //         return visitChildren(ctx);
            //     }

            //     virtual antlrcpp::Any visitValue(JSONParser::ValueContext *ctx) override
            //     {
            //         return visitChildren(ctx);
            //     }
        };

    public:
        parser(ifstream &input) : _input(input), _lexer(&_input), _tokens(&_lexer), _parser(&_tokens)
        {
        }

        void parse()
        {
            JsonRpcParser::ParseContext *_tree;

            _tree = _parser.parse();

            cout << _tree->toStringTree(&_parser) << endl;

            // visitor visitor;
            // return visitor.visitJson(_tree);
        }

        // void print()
        // {
        //     cout << _tree->toStringTree(&_parser) << endl;
        // }

    private:
        ANTLRInputStream _input;
        JsonRpcLexer _lexer;
        CommonTokenStream _tokens;
        JsonRpcParser _parser;
    };
}