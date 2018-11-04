# Mini search engine implementation

- Course Project of System Programming Course.

- Implemented in C++ creating Data Structures like Trie and Posting Lists for
representation of Inverted Index.

- Also used Polymorphism so as to minimize the memory usage for storing each
word into Trie .

## Compile

- being in root folder run **make**

## Execute

- being in root folder run **./build/minisearch -i docfile -k K**
```
- where docfile is the name of the file which contains the documents to be
    stored in the program
- where K is the parameter which indicates the number of results that should
    be returned in each query
```
## Interface

- Options that can be given when the program is in running mode
```
- /search q1 q2 ... q10
    search for given words into documents
- /df
    print the document frequency of the vector
- /tf id word
    print the term frequency of the specific word in document with
    specific id
- /exit
    exit from the application
```

## Example to run

- **./build/minisearch -i ./Dataset/smallDataset.txt -k 10**
