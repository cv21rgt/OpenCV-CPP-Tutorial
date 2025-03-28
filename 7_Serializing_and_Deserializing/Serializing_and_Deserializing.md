# Introduction

:notebook_with_decorative_cover: Thus far we have discussed OpenCV various data types (including `cv::Mat`, `cv::Vec`, `cv::Matx`, `cv::SparseMat`, `cv::Scalar` etc.). In all the example code we have provided, we had to hardcode these data types in our programs in order to make our examples easier to follow. However, this is not how real world applications work - in most cases you need to read such data types as input into your program from an external file (also known as **deserializing**). You also sometimes need to save/write your results to a file for future reference (also known as **serializing**).

:notebook_with_decorative_cover: OpenCV currently uses 3 file formats to serialize or deserialize OpenCV data types: **XML**, **YMAL** and **JSON**.

## XML - eXtensible Markup Language

:notebook_with_decorative_cover: This is a markup language much like HTML. Information in **XML** is wrapped in tags. The tags are not predefined in an **XML** standard unlike HTML tags. The author of the **XML** document gets to choose which tags to use as long as they are meaningful for them when deciphering the information. 

:notebook_with_decorative_cover: **XML** is extensible - meaning even if we add or remove new data, the older version of the document will still work as expected. 

:notebook_with_decorative_cover: To write an **XML** file use the extension `.xml`. 

:notebook_with_decorative_cover: Lets look at a simple example of an **XML** file below:

*student_record.xml*
```xml
<name>Martin D'vloper</name>
<age>26</age>
<hobbies>painting</hobbies>
<hobbies>playing_music</hobbies>
<hobbies>cooking</hobbies>
<programming_languages>
  <java>Intermediate</java>
  <python>Advanced</python>
  <javascript>Beginner</javascript>
</programming_languages>
<favorite_food>
  <vegetables>tomatoes</vegetables>
</favorite_food>
<favorite_food>
  <fruits>
    <citrics>oranges</citrics>
    <tropical>bananas</tropical>
    <nuts>peanuts</nuts>
    <sweets>raisins</sweets>
  </fruits>
</favorite_food>
```

:notebook_with_decorative_cover:: The file above consists of plain text and tags. The tags are enclosed within angle brackets. Tags come in pairs, the opening `<>` and closing tag `</>` . The actual data being stored is found between the opening and closing tags e.g. `<age>26</age>`, `<age>` is the opening tag, `26` is the data, and `</age>` is the closing tag. 
 
:notebook_with_decorative_cover: In this example, the `XML` file is storing data pertaining to a student name, age, hobbies, skill levels for each programming language they know as well as their favourite vegetables and fruits. 

:notebook_with_decorative_cover: While plain text represents the data, tags indicate what the data is. Each tag represents a type of data, like `name`, `age` or `hobbies`. 

## YAML 

:notebook_with_decorative_cover: Originally **YAML** was said to mean *Yet Another Markup Language* because it was released in an era that saw a proliferation of markup languages for presentation and connectivity (HTML, XML, SGML, etc). Its initial name was intended as a tongue-in-cheek reference to the technology landscape, referencing its purpose as a markup language with the yet another construct, but it was then repurposed as **YAML Ain't Markup Language**, a recursive acronym, to distinguish its purpose as data-oriented, rather than document markup. 

:notebook_with_decorative_cover: To write a file using **YAML** use the extension `.yml` or `.yaml`. 

:notebook_with_decorative_cover: When writing **YAML** files you need to know the following rules:

1. **YAML** files use Python-style indentation to determine the structure and indicate nesting. 

2. Tab characters are not allowed by design, to maintain portability across systems, so whitespaces—literal space characters—are used instead. 

3. Comments can be identified with a pound or hash symbol (`#`). It’s always a best practice to use comments, as they describe the intention of the code. **YAML** does not support multi-line comments, each line needs to be suffixed with the pound character. Comments are ignored when reading the data just like in any programming language. 

4. **YAML** uses 3 dashes (`---`) to signal the start of a document.  

5. **YAML** files are mainly made up of **sequence** and **map** (key-value pairs) structures. 

6. **Map**'s allow you to associate key-value pairs. Each key must be unique, and the order doesn't matter. Think of a Python dictionary. Each map has a parent name and then you can have the key-value pairs. Appropriate indentation separates key-values pairs from the parent. Key-value pairs are seperated by a single colon `:`. character. 

7. A **sequence** includes values listed in a specific order and may contain any number of items needed. You can think of a sequence as a Python list or an array in Bash or Perl. A sequence also has a parent name that groups the list items. The actual items start with a dash (`-`) and a space, while indentation separates it from the parent.  

8. A **sequence** can be embedded into a **map** and vice-versa.

9. **YAML** also contains scalars, which are arbitrary data (encoded in Unicode) that can be used as values such as strings, integers, dates, numbers, or booleans.

:notebook_with_decorative_cover: When creating a **YAML** file, you’ll need to ensure that you follow these syntax rules. This is not an exhaustive list of **YAML** syntax rules. Visit this <a href = "https://www.cloudbees.com/blog/yaml-tutorial-everything-you-need-get-started">page</a> for more details.

:notebook_with_decorative_cover: After you write your **YAML** file you need to check that your file is valid. To achieve it, you can use a **linter** — an application that verifies the syntax of a file. One such package is <a href = "https://pypi.org/project/yamllint/">yamllint</a>. It is a python package. If you don't want to deal with Python copy and paste the contents of your **YAML** file to this <a href = "https://www.yamllint.com/">site</a> - it will check if you have created a valid **YAML** file before you hand it over to an application.

:notebook_with_decorative_cover: We will show the same file from above (`student_record.xml`) as a **YAML** file:

*student_record.yaml*
```yaml
# Comment: Student record
# Describes some characteristics and preferences
--- # Signals start of document
name: Martin D'vloper # key-value pair
age: 26
hobbies: # Name of sequence/list
  - painting # First list item
  - playing_music # Second list item
  - cooking # Third list item
programming_languages: # Name of map
  java: Intermediate # Programming language and skill level
  python: Advanced
  javascript: Beginner
favorite_food: 
  - vegetables: tomatoes 
  - fruits: # Map embedded in a sequence/list
      citrics: oranges 
      tropical: bananas
      nuts: peanuts
      sweets: raisins
```

:notebook_with_decorative_cover: We can see that for this student record, we save the student name and age as maps. Hobbies are saved as a List/Sequence. A Map has been used to associate each unique programming language with the level of skills for the student. The student's favourite food are first placed in a List of two items (vegetables and fruits), which are then broken down further into mappings associating each main class of vegetable or fruit with a specific fruit or vegetable. The file also provides single line comments.



## JSON

:notebook_with_decorative_cover: **JavaScript Object Notation (JSON)** is a very common standard text-based format for representing structured data based on JavaScript object syntax. To create such a file use the extension `.json`.

:notebook_with_decorative_cover: **JSON** files are a collection of key-value pairs, where the **key** must be a **string** type, and the value can be of any of the types: number (integer or float), string, booloean, array, object, null.

:notebook_with_decorative_cover: There are some simple rules you have to maintain to create a valid JSON file:

1. In the **JSON** data format, the keys must be strings and enclosed in double quotes `""`.

2. The key and value must be separated by a colon (`:`) symbol.

3. Strings should be placed in double quotes, while numbers are not.

4. Data is seperated by commas (`,`).

5. No comments are allowed in JSON files. But you can <a href = "https://www.freecodecamp.org/news/json-comment-example-how-to-comment-in-json-files/">get around that</a>, if you're curious.

6. Valid **JSON** data can be in two different formats:

* A collection of key-value pairs enclosed by a pair of curly braces `{...}`. This is the equivalent of a MAP in a **YAML** file. 

* A collection of an ordered list of key-value pairs separated by comma (`,`) and enclosed by a pair of square brackets `[...]` e.g. an array. This is the equivalent of a Sequence/List in a **YAML** file. 

:notebook_with_decorative_cover: **JSON** file format has been around since the early 2000s - which means there is a lot of literature out there if you want to be an expert on it. 

:notebook_with_decorative_cover: Our previous example can be written as a **JSON** file as follows:

*student_record.json*
```json
{
    "name": "Martin D'vloper",
    "age": 26,
    "hobbies": [
      "painting",
      "playing_music",
      "cooking"
    ],
    "programming_languages": {
      "java": "Intermediate",
      "python": "Advanced",
      "javascript": "Beginner"
    },
    "favorite_food": [
      {
        "vegetables": "tomatoes"
      },
      {
        "fruits": {
          "citrics": "oranges",
          "tropical": "bananas",
          "nuts": "peanuts",
          "sweets": "raisins"
        }
      }
    ]
  }
```

:notebook_with_decorative_cover: By looking at the above 3 examples - **XML**, **YAML** and **JSON** file formats all use the same basic concepts especially **Lists** and **Maps** to store grouped data.

:notebook_with_decorative_cover: We should also mention that OpenCV also allows you to work with compressed files. All you have to do is append `.gz` at the end of the file extension e.g. `student_record.xml.gz`.