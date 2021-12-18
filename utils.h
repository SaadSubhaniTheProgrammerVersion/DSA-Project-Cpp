

bool invalid_char(char c) {
	return !isprint( static_cast<unsigned char>( c ) );
}

void my_remove(std::string& s, char a)
{ 
	s.erase(std::remove(s.begin(),s.end(),a),s.end());
}

std::vector<std::string> split(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        if (end != start) {
          tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
       tokens.push_back(text.substr(start));
    }
    return tokens;
}


std::vector<std::string> sanitize_and_stem_list(std::vector<std::string> input) {
	std::vector<std::string> output;
	std::string word;
	std::string chars = "\n{}[]()!@#$% ^&*-—_=+/?.>,<;:`\"1234567890";

	for (int i = 0; i < input.size(); i++) {
		word = input[i];
		
		//word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
    	/*for (char c: word) { // Remove chars that are not alphabet
			if (c > 123 || c < 96)
				my_remove(word, c);
			//if (c > 123 || c < 96 || !(isprint(c)))
        	//	word.erase(std::remove(word.begin(), word.end(), c), word.end());
		}*/

		size_t j = 0;
		size_t len = word.length();
		while(j < len){
			if (!std::isalpha(word[j]) || word[j] == '\n'){
				word.erase(j,1);
				len--;
			}else
				j++;
		}


		std::transform(word.begin(), word.end(), word.begin(),
    		[](unsigned char c){ return std::tolower(c); });

		std::wstring wstr (word.begin(), word.end());
		stemming::english_stem<> Stem;
		Stem(wstr);
		std::string stemmed = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
		if(!(word.length() < 2 && word.length() > 30)) {
			//std::cout << temp << "\n";
			output.push_back(stemmed);
		}
	}

	return output;
}