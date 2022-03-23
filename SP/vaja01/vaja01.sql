-- MariaDB dump 10.19  Distrib 10.5.12-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: school
-- ------------------------------------------------------
-- Server version	10.5.12-MariaDB-1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ad`
--

DROP TABLE IF EXISTS `ad`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ad` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL,
  `description` varchar(255) NOT NULL,
  `date_s` int(11) NOT NULL DEFAULT unix_timestamp(),
  `date_e` int(11) NOT NULL DEFAULT (unix_timestamp() + 2592000),
  `seen` int(10) unsigned NOT NULL DEFAULT 0,
  `userID` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `userID` (`userID`),
  CONSTRAINT `ad_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `user` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=72 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ad`
--

LOCK TABLES `ad` WRITE;
/*!40000 ALTER TABLE `ad` DISABLE KEYS */;
INSERT INTO `ad` VALUES (1,'Kupim 10 kg pasje hrane Courigan','Prejšni mesec so prenehali izdelovati hrano podjetja Courigan, ki je bil moji psici Tački edina okusna hrana. Prodajalcu plačam dvakratno ceno nabavne cene, ki je znašala 5€ na kg.',1647760653,1650352653,0,0),(2,'Golf počitnice','Bi rad se malo spočil od napornega dela v službi in imaš rad golf. Kaj še čakaš? Pridi na naš spletni portal https://golf-pocitnice.si, kjer lahko ti osvojiš brezplačni oddih na golf hotelu Topolšček',1647760653,1650352653,1421,0),(3,'Harry Potter knjige/filmi','Rada bi kupila vse knjige/filme od J.K. Rowling Harry Potter. V kolekciji imam še prve 3 knjige serije in 1. film, ostale pa bi rada kupila. Pišite samo resne stranke.',1647760653,1650352653,1,0),(4,'dasdas','Dsadasdasdsad',1647805370,1650397370,0,3),(5,'','Description',1647806809,1650398809,0,3),(6,'dasdas','Description',1647807019,1650399019,0,3),(7,'dasdsa','Description',1647807232,1650399232,0,3),(8,'dasdsa','Description',1647807333,1650399333,0,3),(9,'dsadasda','Description',1647807346,1650399346,0,3),(10,'dadas','Description',1647807984,1650399984,0,3),(11,'nekaj','seveda',1647808005,1650400005,0,3),(12,'nekaj','seveda',1647808046,1650400046,0,3),(13,'dasdas','adsasdasd',1647808172,1650400172,0,3),(14,'dadsa','Descriptiondasdas',1647808612,1650400612,0,3),(15,'dassdas','Descriptiondasdas',1647808618,1650400618,0,3),(16,'dassdas','Descriptiondasdas',1647808621,1650400621,0,3),(17,'dasdas','Description',1647808710,1650400710,0,3),(18,'dasdas','Description',1647808823,1650400823,0,3),(19,'dasdas','Description',1647808823,1650400823,0,3),(20,'dasdas','Description',1647808843,1650400843,0,3),(21,'dasdas','Description',1647808897,1650400897,0,3),(22,'dasdasd','Description',1647809172,1650401172,0,3),(23,'dasdasd','Description',1647809210,1650401210,0,3),(24,'Prosim','Description',1647809621,1650401621,0,3),(25,'dasdas','Description',1647810189,1650402189,0,3),(26,'dasdas','Description',1647810333,1650402333,0,3),(38,'dasdas','Descriptiondasd',1647814167,1650406167,0,4),(39,'dasdas','Descriptiondasd',1647814182,1650406182,0,4),(40,'dasdas','Descriptiondasd',1647814227,1650406227,0,4),(41,'dasdas','Descriptionsadas',1647814237,1650406237,0,4),(42,'dasdas','Descriptionsadas',1647814269,1650406269,0,4),(43,'dasda','Descriptionsadasdasdasa',1647814277,1650406277,0,4),(44,'dasda','Descriptionsadasdasdasa',1647814410,1650406410,0,4),(45,'dasda','Descriptionsadasdasdasa',1647814450,1650406450,0,4),(46,'dasdasd','Description',1647814472,1650406472,0,4),(47,'dasdasd','Description',1647814485,1650406485,0,4),(48,'dasdasd','Description',1647814486,1650406486,0,4),(49,'dasdas','Description',1647814499,1650406499,0,4),(50,'dasdas','Description',1647814584,1650406584,0,4),(51,'asdsadas','Description',1647814592,1650406592,0,4),(52,'asdsadas','Description',1647814674,1650406674,0,4),(53,'asdsadas','Description',1647815356,1650407356,0,4),(54,'asdsadas','Description',1647815358,1650407358,0,4),(55,'asdsadas','Description',1647815379,1650407379,0,4),(56,'asdsadas','Description',1647815539,1650407539,0,4),(57,'asdsadas','Description',1647815641,1650407641,0,4),(58,'asdsadas','Description',1647815714,1650407714,0,4),(59,'asdsadas','Description',1647815757,1650407757,0,4),(60,'asdsadas','Description',1647815832,1650407832,0,4),(61,'asdsadas','Description',1647815846,1650407846,0,4),(62,'asdsadas','Description',1647816118,1650408118,0,4),(63,'asdsadas','Description',1647816121,1650408121,0,4),(64,'asdsadas','Description',1647816147,1650408147,0,4),(65,'asdsadas','Description',1647816255,1650408255,0,4),(66,'asdsadas','Description',1647816270,1650408270,0,4),(67,'asdsadas','Description',1647816433,1650408433,0,4),(68,'asdsadas','Description',1647816442,1650408442,0,4),(69,'dadsa','Descriptiondsadasd',1647816452,1650408452,0,4),(70,'dadsa','Descriptiondsadasd',1647816528,1650455906,0,4);
/*!40000 ALTER TABLE `ad` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ad_category`
--

DROP TABLE IF EXISTS `ad_category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ad_category` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `adID` int(10) unsigned NOT NULL,
  `categoryID` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `fk_add` (`adID`),
  KEY `fk_category` (`categoryID`),
  CONSTRAINT `fk_add` FOREIGN KEY (`adID`) REFERENCES `ad` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_category` FOREIGN KEY (`categoryID`) REFERENCES `category` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=181 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ad_category`
--

LOCK TABLES `ad_category` WRITE;
/*!40000 ALTER TABLE `ad_category` DISABLE KEYS */;
INSERT INTO `ad_category` VALUES (7,1,8),(8,1,12),(9,2,1),(10,2,3),(11,2,11),(12,2,14),(13,3,5),(14,3,7),(15,3,9),(16,10,1),(18,11,1),(20,12,1),(22,13,3),(24,20,2),(26,21,2),(28,22,1),(30,23,1),(32,24,1),(33,25,1),(35,26,1),(36,26,2),(37,26,3),(38,26,4),(74,38,2),(75,38,3),(76,38,4),(77,39,2),(78,39,3),(79,40,2),(80,40,3),(81,41,1),(82,41,2),(83,41,3),(84,42,1),(85,42,2),(86,42,3),(87,43,2),(88,43,3),(89,44,2),(90,44,3),(91,45,2),(92,45,3),(93,46,2),(94,46,3),(95,47,2),(96,47,3),(97,48,2),(98,48,3),(99,49,1),(100,49,2),(101,50,1),(102,50,2),(103,51,1),(104,51,2),(105,51,3),(106,52,1),(107,52,2),(108,52,3),(109,53,1),(110,53,2),(111,53,3),(112,54,1),(113,54,2),(114,54,3),(115,55,1),(116,55,2),(117,55,3),(118,56,1),(119,56,2),(120,56,3),(121,57,1),(122,57,2),(123,57,3),(124,58,1),(125,58,2),(126,58,3),(127,59,1),(128,59,2),(129,59,3),(130,60,1),(131,60,2),(132,60,3),(133,61,1),(134,61,2),(135,61,3),(136,62,1),(137,62,2),(138,62,3),(139,63,1),(140,63,2),(141,63,3),(142,64,1),(143,64,2),(144,64,3),(145,65,1),(146,65,2),(147,65,3),(148,66,1),(149,66,2),(150,66,3),(151,67,1),(152,67,2),(153,67,3),(154,68,1),(155,68,2),(156,68,3),(157,69,1),(158,69,2),(159,69,3),(160,69,4),(161,70,1),(162,70,2),(163,70,3),(164,70,4),(165,70,1),(166,70,2),(167,70,3),(168,70,4);
/*!40000 ALTER TABLE `ad_category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `category` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `pID` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `pID` (`pID`),
  CONSTRAINT `category_ibfk_1` FOREIGN KEY (`pID`) REFERENCES `category` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` VALUES (1,'sport',NULL),(2,'news',NULL),(3,'job/work',NULL),(4,'clothes',NULL),(5,'free time/hobies',NULL),(6,'music',NULL),(7,'movies',NULL),(8,'food',NULL),(9,'books',NULL),(10,'TV',NULL),(11,'travel',NULL),(12,'pets',NULL),(13,'restaurant',NULL),(14,'holiday',NULL),(15,'basketball',1),(16,'hockey',1),(17,'golf',1),(18,'NBA',15),(19,'NHL',16);
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `image`
--

DROP TABLE IF EXISTS `image`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `image` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `img` longblob NOT NULL,
  `adID` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `adID` (`adID`),
  CONSTRAINT `image_ibfk_1` FOREIGN KEY (`adID`) REFERENCES `ad` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `image`
--

LOCK TABLES `image` WRITE;
/*!40000 ALTER TABLE `image` DISABLE KEYS */;
/*!40000 ALTER TABLE `image` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `uname` varchar(255) NOT NULL,
  `pass` varchar(64) NOT NULL,
  `email` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `phone` varchar(15) DEFAULT NULL,
  `gender` enum('male','female','undefined/non binary') DEFAULT NULL,
  `age` tinyint(3) unsigned DEFAULT NULL,
  `address` varchar(255) DEFAULT NULL,
  `bday` date DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `uname` (`uname`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (3,'test','9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08','test@test','testing','gnitset','031234567','male',NULL,'addr','2000-03-20'),(4,'admin','8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918','admin@admin','admin','admin','admin','male',NULL,'admin','1999-02-01');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-03-21 13:29:09
