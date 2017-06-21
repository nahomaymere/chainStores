#include "splitter.h"


const unsigned int SPLIT_ERROR = 0;

Splitter::Splitter(const string& string_to_split):
    original_string_(string_to_split), split_result_( {} ) {
}
void Splitter::set_string_to_split(const string& string_to_split) {
    original_string_ = string_to_split;
    split_result_ = {};
}

unsigned int Splitter::split(char separator, bool skip_empty_fields) {
    // split_result_ vector needs to be emptied in case someone
    // ends up accidentally calling split method twice in a row.
    split_result_.clear();

    // startpos is a bookkeeping variable which keeps track of
    // the starting position (index) of the next field inside the
    // string we are trying to split.
    string::size_type startpos = 0;
    string field_content;

    while ( true ) {
        // We need to find the position of the next separator
        // starting from startpos.  The location of the separator
        // is stored into endpos.
        string::size_type endpos;

        endpos = original_string_.find(separator, startpos);

        // If separator can not be found the rest of the string
        // from startpos forward must be the last field of the
        // string.  That will get a sepatare treatment after the loop.
        if ( endpos == string::npos ) {
            break;
        }

        // The content of the current field lays between startpos
        // and endpos (the character at the endpos is not included).
        field_content = original_string_.substr(startpos, endpos - startpos);

        // Empty fields are skipped is skip_empty_fields is true.
        if ( not (skip_empty_fields and field_content.empty()) ) {
            // We end up here if field was not skipped.
            split_result_.push_back(field_content);
        }

        // The next field will be starting from character
        // that comes after the separator at endpos.
        startpos = endpos + 1;
    }

    // We need to store the field after the last separator.
    // The loop above didn't store the last field.
    field_content = original_string_.substr(startpos);

    if ( not (skip_empty_fields and field_content.empty()) ) {
        split_result_.push_back(field_content);
    }

    return split_result_.size();
}


unsigned int Splitter::number_of_fields() const {
    // Splitting has not been done yet if split_result_ is epmty.
    // That is an error condition.
    if ( split_result_.size() == 0 ) {
        return SPLIT_ERROR;

    } else {

        return split_result_.size();
    }
}


string Splitter::fetch_field(unsigned int field_index) const {
    // Splitting has not been done yet if split_result_ is epmty.
    // That is an error condition.
    if ( split_result_.empty() or field_index >= split_result_.size() ) {
        // A simple example of using/raising/throwin exception in C++.
        // If the excetion is not handled/caught somewhere, the
        // program will end.
        throw out_of_range("too large index or split not called");
    }

    return split_result_.at(field_index);
}
