# This is markdown files converter

## Context
This application will be able to convert markdown files to html. 
This converter will give powerful and simple to use command-line interface for users, 
and it will be easy to integrate it with other Unix applications like xargs. 
This project will be useful for web-and-not-only-developers, as it will be able to parse .md to .html

Parsing table:
```
**bold text**          | <b>bold text</b>
__italic text__        | <i>italic text</i>
`monospaced`           | <tt>bold text</tt>
```preformated text``` | <pre>bold text</pre>

Paragraph 1.           | <p>Paragraph 1.</p>
                       | <p>Paragraph 2.</p>
Paragraph 2.           | 
```
## Goals:
* correct parsing from markdown to html
* fast conversion 
* simple CLI usage
* integration ability
* ability to painlessly extend behaviour of parser (for example, markdown to terminal conversion)
## Non-goals:
* reverse parsing (for now, at least)
* no nested tags processing (for example, \*\*\_\_safd__** will throw an error)
* processing of files, that possibly could overload RAM of device (files that take > 4gb memory)
## Design:
To be able to extend the project, it will need separate design:
* commands processor for CLI
  * responsive for processing --out flag
* small parsers for each type of tag, so it is easy to add or replace one
* line parser, that checks and parses line
* paragraphs parser, that checks text on paragraphs
* file iterator, that reads it line by line and passes to line-parser or paragraphs parser
* OS interface, for reading and writing files from/to disk
  * writes to a file if --out /path/to/html.html were provided (or to ./out.html if no path were provided)
  * writes to stdout if no --out were passed to CLI
  * writes to stderr if error occurred
