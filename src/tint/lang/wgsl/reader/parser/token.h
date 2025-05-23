// Copyright 2020 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef SRC_TINT_LANG_WGSL_READER_PARSER_TOKEN_H_
#define SRC_TINT_LANG_WGSL_READER_PARSER_TOKEN_H_

#include <string>
#include <string_view>
#include <variant>

#include "src/tint/utils/diagnostic/source.h"

namespace tint::wgsl::reader {

/// Stores tokens generated by the Lexer
class Token {
  public:
    /// The type of the parsed token
    enum class Type {
        /// Error result
        kError = -2,
        /// Uninitialized token
        kUninitialized = 0,
        /// Placeholder token which maybe filled in later
        kPlaceholder = 1,
        /// End of input string reached
        kEOF,

        /// An identifier
        kIdentifier,
        /// A float literal with no suffix
        kFloatLiteral,
        /// A float literal with an 'f' suffix
        kFloatLiteral_F,
        /// A float literal with an 'h' suffix
        kFloatLiteral_H,
        /// An integer literal with no suffix
        kIntLiteral,
        /// An integer literal with an 'i' suffix
        kIntLiteral_I,
        /// An integer literal with a 'u' suffix
        kIntLiteral_U,

        /// A '&'
        kAnd,
        /// A '&&'
        kAndAnd,
        /// A '->'
        kArrow,
        /// A '@'
        kAttr,
        /// A '/'
        kForwardSlash,
        /// A '!'
        kBang,
        /// A '['
        kBracketLeft,
        /// A ']'
        kBracketRight,
        /// A '{'
        kBraceLeft,
        /// A '}'
        kBraceRight,
        /// A ':'
        kColon,
        /// A ','
        kComma,
        /// A '='
        kEqual,
        /// A '=='
        kEqualEqual,
        /// A '>' (post template-args classification)
        kTemplateArgsRight,
        /// A '>'
        kGreaterThan,
        /// A '>='
        kGreaterThanEqual,
        /// A '>>'
        kShiftRight,
        /// A '<' (post template-args classification)
        kTemplateArgsLeft,
        /// A '<'
        kLessThan,
        /// A '<='
        kLessThanEqual,
        /// A '<<'
        kShiftLeft,
        /// A '%'
        kMod,
        /// A '-'
        kMinus,
        /// A '--'
        kMinusMinus,
        /// A '!='
        kNotEqual,
        /// A '.'
        kPeriod,
        /// A '+'
        kPlus,
        /// A '++'
        kPlusPlus,
        /// A '|'
        kOr,
        /// A '||'
        kOrOr,
        /// A '('
        kParenLeft,
        /// A ')'
        kParenRight,
        /// A ';'
        kSemicolon,
        /// A '*'
        kStar,
        /// A '~'
        kTilde,
        /// A '_'
        kUnderscore,
        /// A '^'
        kXor,
        /// A '+='
        kPlusEqual,
        /// A '-='
        kMinusEqual,
        /// A '*='
        kTimesEqual,
        /// A '/='
        kDivisionEqual,
        /// A '%='
        kModuloEqual,
        /// A '&='
        kAndEqual,
        /// A '|='
        kOrEqual,
        /// A '^='
        kXorEqual,
        /// A '>>='
        kShiftRightEqual,
        /// A '<<='
        kShiftLeftEqual,

        /// A 'alias'
        kAlias,
        /// A 'break'
        kBreak,
        /// A 'case'
        kCase,
        /// A 'const'
        kConst,
        /// A 'const_assert'
        kConstAssert,
        /// A 'continue'
        kContinue,
        /// A 'continuing'
        kContinuing,
        /// A 'default'
        kDefault,
        /// A 'diagnostic'
        kDiagnostic,
        /// A 'discard'
        kDiscard,
        /// A 'else'
        kElse,
        /// A 'enable'
        kEnable,
        /// A 'fallthrough'
        // Note, this isn't a keyword, but a reserved word. We match it as a keyword in order to
        // provide better diagnostics in case a `fallthrough` is added to a case body.
        kFallthrough,
        /// A 'false'
        kFalse,
        /// A 'fn'
        kFn,
        // A 'for'
        kFor,
        /// A 'if'
        kIf,
        /// A 'let'
        kLet,
        /// A 'loop'
        kLoop,
        /// A 'override'
        kOverride,
        /// A 'requires'
        kRequires,
        /// A 'return'
        kReturn,
        /// A 'struct'
        kStruct,
        /// A 'switch'
        kSwitch,
        /// A 'true'
        kTrue,
        /// A 'var'
        kVar,
        /// A 'while'
        kWhile,
    };

    /// Converts a token type to a name
    /// @param type the type to convert
    /// @returns the token type as as string
    static std::string_view TypeToName(Type type);

    /// Creates an uninitialized token
    Token();
    /// Create a Token
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    Token(Type type, const Source& source);

    /// Create a string Token
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    /// @param view the source string view for the token
    Token(Type type, const Source& source, std::string_view view);
    /// Create a string Token
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    /// @param str the source string for the token
    Token(Type type, const Source& source, const std::string& str);
    /// Create a string Token
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    /// @param str the source string for the token
    Token(Type type, const Source& source, const char* str);
    /// Create a integer Token of the given type
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    /// @param val the source unsigned for the token
    Token(Type type, const Source& source, int64_t val);
    /// Create a double Token
    /// @param type the Token::Type of the token
    /// @param source the source of the token
    /// @param val the source double for the token
    Token(Type type, const Source& source, double val);
    /// Move constructor
    Token(Token&&);
    ~Token();

    /// Equality operator with an identifier
    /// @param ident the identifier string
    /// @return true if this token is an identifier and is equal to ident.
    bool operator==(std::string_view ident) const;

    /// Sets the token to the given type
    /// @param type the type to set
    void SetType(Token::Type type) { type_ = type; }

    /// Returns true if the token is of the given type
    /// @param t the type to check against.
    /// @returns true if the token is of type `t`
    bool Is(Type t) const { return type_ == t; }

    /// @returns true if the token is uninitialized
    bool IsUninitialized() const { return type_ == Type::kUninitialized; }
    /// @returns true if the token is a placeholder
    bool IsPlaceholder() const { return type_ == Type::kPlaceholder; }
    /// @returns true if the token is EOF
    bool IsEof() const { return type_ == Type::kEOF; }
    /// @returns true if the token is Error
    bool IsError() const { return type_ == Type::kError; }
    /// @returns true if the token is an identifier
    bool IsIdentifier() const { return type_ == Type::kIdentifier; }
    /// @returns true if the token is a literal
    bool IsLiteral() const {
        return type_ == Type::kIntLiteral || type_ == Type::kIntLiteral_I ||
               type_ == Type::kIntLiteral_U || type_ == Type::kFalse || type_ == Type::kTrue ||
               type_ == Type::kFloatLiteral || type_ == Type::kFloatLiteral_F ||
               type_ == Type::kFloatLiteral_H;
    }

    /// @returns the number of placeholder tokens required to follow the token, in order to provide
    /// space for token splitting.
    size_t NumPlaceholders() const {
        switch (type_) {
            case Type::kShiftRightEqual:
                return 2;
            case Type::kShiftRight:
            case Type::kGreaterThanEqual:
            case Type::kAndAnd:
            case Type::kMinusMinus:
                return 1;
            default:
                return 0;
        }
    }

    /// @returns true if the token is a binary operator
    bool IsBinaryOperator() const {
        switch (type_) {
            case Type::kAnd:
            case Type::kAndAnd:
            case Type::kEqualEqual:
            case Type::kForwardSlash:
            case Type::kGreaterThan:
            case Type::kGreaterThanEqual:
            case Type::kLessThan:
            case Type::kLessThanEqual:
            case Type::kMinus:
            case Type::kMod:
            case Type::kNotEqual:
            case Type::kOr:
            case Type::kOrOr:
            case Type::kPlus:
            case Type::kShiftLeft:
            case Type::kShiftRight:
            case Type::kStar:
            case Type::kXor:
                return true;
            default:
                return false;
        }
    }

    /// @returns the source information for this token
    Source source() const { return source_; }

    /// @returns the type of the token
    Type type() const { return type_; }

    /// Returns the string value of the token
    /// @return std::string
    std::string to_str() const;
    /// Returns the string view of the token
    /// @return std::string_view
    /// @note if the token is not an identifier, an empty string_view will be returned.
    std::string_view to_str_view() const;
    /// Returns the float value of the token. 0 is returned if the token does not
    /// contain a float value.
    /// @return double
    double to_f64() const;
    /// Returns the int64_t value of the token. 0 is returned if the token does
    /// not contain an integer value.
    /// @return int64_t
    int64_t to_i64() const;

    /// @returns the token type as string
    std::string_view to_name() const { return Token::TypeToName(type_); }

  private:
    /// The Token::Type of the token
    Type type_ = Type::kError;
    /// The source where the token appeared
    Source source_;
    /// The value represented by the token
    std::variant<int64_t, double, std::string, std::string_view> value_;
};

template <typename STREAM>
    requires(traits::IsOStream<STREAM>)
auto& operator<<(STREAM& out, Token::Type type) {
    out << Token::TypeToName(type);
    return out;
}

}  // namespace tint::wgsl::reader

#endif  // SRC_TINT_LANG_WGSL_READER_PARSER_TOKEN_H_
