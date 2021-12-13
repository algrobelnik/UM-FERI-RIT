use std::io;
use std::io::Write;
use std::str::{self, FromStr};
use std::fmt::{self, Display, Debug, Formatter};
use std::error::Error;
use std::any::type_name;
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

fn type_of<T>(_: T) -> &'static str {
    type_name::<T>()
}
#[derive(Debug, PartialEq)]
enum ParseContentError {
    Empty,
    NoName,
    NoSurname,
    NoPhone,
    BadLen,
    AlreadyExists,
    DoesntExists,
}

impl Error for ParseContentError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        match *self {
            Self::Empty => None,
            Self::NoName => None,
            Self::NoSurname => None,
            Self::NoPhone => None,
            Self::BadLen => None,
            Self::AlreadyExists => None,
            Self::DoesntExists => None,
        }
    }
}
impl Display for ParseContentError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        match &self {
            Self::Empty => return write!(f, "Empty string"),
            Self::NoName => return write!(f, "No name"),
            Self::NoSurname => return write!(f, "No surname"),
            Self::NoPhone => return write!(f, "No phone"),
            Self::BadLen => return write!(f, "Bad lenght"),
            Self::AlreadyExists => return write!(f, "Already exists"),
            Self::DoesntExists => return write!(f, "Doesn't exists"),
        }
    }
}

struct Directory {
    name: String,
    val: Vec<Content>,
}

impl Directory {
    fn new(n: String) -> Self {
        Directory{
            name: n,
            val: Vec::<Content>::new(),
        }
    }
    fn add(&mut self, c: Content) {
        let _ = &self.val.push(c);
    }
    fn delete(&mut self, c: Content) {
        let mut index = self.val.len();
        let _ = &self.val.iter().enumerate().for_each(|(i, x)| {
            if x.phone == c.phone {
                index = i;
            }
        });
        if index == self.val.len() {
            println!("Index out of range");
            return;
        }
        let _ = &self.val.remove(index);
    }

    fn find(&mut self, s: String) -> Result<&Content, ParseContentError> {
        for x in &self.val {
            if x.phone == s {
                return Ok(x);
            }
        };
        Err(ParseContentError::DoesntExists)
    }
    
    fn search(&mut self, s: String) -> Result<Vec<&Content>, ParseContentError> {
        let mut vec = Vec::<&Content>::new();
        for x in &self.val {
            if x.name.contains(&s) {
                vec.push(x);
            }
            if x.surname.contains(&s) {
                vec.push(x);
            }
            if x.phone.contains(&s) {
                vec.push(x);
            }
        };
        if vec.len() != 0 {
            Ok(vec)
        }else {
            Err(ParseContentError::DoesntExists)
        }
    }
}

#[derive(PartialEq, PartialOrd)]
struct Content {
    name: String,
    surname: String,
    phone: String,
}

impl FromStr for Content {
    type Err = ParseContentError;
    fn from_str(s: &str) -> Result<Content, Self::Err> {
        if s.is_empty(){
            return Err(ParseContentError::Empty);
        }
        let split: Vec<&str> = s.split(" ").collect();
        if split.len() != 3 || split[0].to_string().is_empty() || split[1].to_string().is_empty() || split[2].to_string().is_empty() || split[0].len() > 100 || split[1].len() > 100 || split[2].len() > 30{
            if split.len() != 3 {
                return Err(ParseContentError::BadLen);
            } else if split[0].to_string().is_empty() || split[0].len() > 100 {
                return Err(ParseContentError::NoName);
            } else if split[1].to_string().is_empty() || split[1].len() > 100 {
                return Err(ParseContentError::NoSurname);
            } else if split[2].to_string().is_empty() || split[2].len() > 30 {
                return Err(ParseContentError::NoPhone);
            }
        }
        let n: &str = split[0];
        let s: &str = split[1];
        let p: &str = split[2];
        let a: &str = n.clone();
        let b: &str = s.clone();
        let c: &str = p.clone();
        Ok(Content {
            name: n.to_string(),
            surname: s.to_string(),
            phone: p.to_string(),
        })
    }
}

impl Debug for Content {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f, "{}", format!("Name: {}|Surname: {}|Phone: {}", self.name, self.surname, self.phone))
    }
}

fn main() {
    let dir = Arc::new(Mutex::new(Directory::new("Imenik".to_string())));
    let mut d = Arc::clone(&dir);
    let mut check = true;
    while check {
        print!("Insert command: ");
        io::stdout().flush().unwrap();
        let mut cmd = String::new();

        io::stdin()
            .read_line(&mut cmd)
            .expect("Failed to readline");

        let temp = cmd.as_str().trim().split(" ");
        let vec = temp.collect::<Vec<&str>>();
        let first = vec.first().unwrap();
        let mut split: Vec<&str> = cmd.split(" ").collect();
        let index = split.iter().position(|x| *x == split[0]).unwrap();
        split.remove(index);
        let mut new_s = String::from("");
        for val in split {
            new_s = new_s.to_owned() + " " + val;
        }
        let res = match first.to_owned() {
            "insert" => insert(&mut d, new_s.as_str().trim().to_string()),
            "delete" => delete(&mut d, new_s.as_str().trim().to_string()),
            "find" => find(&mut d, new_s.as_str().trim().to_string()),
            "search" => search(&mut d, new_s.as_str().trim().to_string()),
            "exit" => exit(&mut check),
            x => nothing(x.to_string()),
        };
        println!("{:?}",res);
        println!("{}",d.lock().unwrap().val.len());
    }
}
fn insert(d: &mut Arc<Mutex<Directory>>, s: String) -> Result<String, Box<dyn Error>>{
    let v = match s.parse::<Content>(){
        Ok(x) => {
            println!("{:?}", x);
            x
        },
        Err(e) => {
            println!("{:?}", e);
            return Err(Box::new(e));
        },
    };
    for i in &d.lock().unwrap().val {
        if i == &v {
            return Err(Box::new(ParseContentError::AlreadyExists));
        }
    }
    d.lock().unwrap().add(v);
    Ok("".to_string())
}

fn delete(d: &mut Arc<Mutex<Directory>>, s: String) -> Result<String, Box<dyn Error>>{
    let mut c: Content = Content {
        name: "EMPTY".to_string(),
        surname: "EMPTY".to_string(),
        phone: s,
    };
    d.lock().unwrap().delete(c);
    Ok("".to_string())
}
fn find(d: &mut Arc<Mutex<Directory>>, s: String) -> Result<String, Box<dyn Error>>{
    let mut dir = d.lock().unwrap();
    let c = match dir.find(s) {
        Ok(v) => v,
        Err(e) => {
            return Err(Box::new(e));
        },
    };
    println!("{:?}", c);
    Ok("".to_string())
}
fn search(d: &mut Arc<Mutex<Directory>>, s: String) -> Result<String, Box<dyn Error>>{
    let mut dir = d.lock().unwrap();
    let c = match dir.search(s) {
        Ok(v) => v,
        Err(e) => {
            return Err(Box::new(e));
        },
    };
    println!("{:?}", c);
    Ok("".to_string())
}
fn exit(check: &mut bool) -> Result<String, Box<dyn Error>>{
    *check = false;
    Ok("Exit".to_string())
}
fn nothing(s: String) -> Result<String, Box<dyn Error>>{
    println!("Command {} not fount", s);
    Ok("".to_string())
}
