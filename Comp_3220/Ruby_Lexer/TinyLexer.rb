#
#  Class Lexer - Reads a TINY program and emits tokens
#
class Lexer
# Constructor - Is passed a file to scan and outputs a token
#               each time nextToken() is invoked.
#   @c        - A one character lookahead 
def initialize(filename)

	# Opens file to read.
	if (File.file?(filename))
		@f = File.open(filename,'r:utf-8')
	else
		puts "File does not exist."
		exit
	end
	
	# Reads first character in the file.
	if (! @f.eof?)
		@c = @f.getc()
	else
		@c = "eof"
		@f.close()
	end

end
	
	# Method nextCh() returns the next character in the file
	def nextCh()
		if (! @f.eof?)
			@c = @f.getc()
		else
			@c = "eof"
		end
		
		return @c
	end

	# Method nextToken() reads characters in the file and returns
	# the next token
	def nextToken() 
		if @c == "eof"
			tok = Token.new(Token::EOF,"eof")
				
		elsif (whitespace?(@c))
			str =""
		
			while whitespace?(@c)
				str += @c
				nextCh()
			end
		
			tok = Token.new(Token::WS, str)
		
		elsif (letter?(@c))
			str = ""
			while (letter?(@c))
				str += @c
				nextCh()
			end

			if str == "print"
				tok = Token.new(Token::RESERVED, str)
			else
				tok = Token.new(Token::VARIABLE, str)
			end

		elsif (numeric?(@c))
			str = ""
			while (numeric?(@c))
				str += @c
				nextCh()
			end
			tok = Token.new(Token::INTEGER, str)


		elsif @c == "("
			nextCh()
			tok = Token.new(Token::LPAREN, "(")

		elsif @c == ")"
			nextCh()
			tok = Token.new(Token::RPAREN, ")")

		elsif @c == "+" || @c == "-" || @c == "*" || @c == "/" || @c == "=" || @c == ">" || @c == "<" || @c == ";" 
			tok = Token.new(Token::OPERATOR, @c)
			nextCh()

		else
			nextCh()
			token = Token.new(Token::UNKNOWN, @c)
		end

		
		return tok
	end
	
end
#
# Helper methods for Scanner
#
def letter?(lookAhead)
	lookAhead =~ /^[a-z]|[A-Z]$/
end

def numeric?(lookAhead)
	lookAhead =~ /^(\d)+$/
end

def whitespace?(lookAhead)
	lookAhead =~ /^(\s)+$/
end