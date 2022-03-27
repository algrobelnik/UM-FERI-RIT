<?php

namespace Database\Seeders;

use Carbon\Carbon;
use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class AdSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
{
    //TODO INSERT INTO `ad` VALUES (1,','',1647760653,1650352653,0,0),(2,'Golf počitnice','Bi rad se malo spočil od napornega dela v službi in imaš rad golf. Kaj še čakaš? Pridi na naš spletni portal https://golf-pocitnice.si, kjer lahko ti osvojiš brezplačni oddih na golf hotelu Topolšček',1647760653,1650352653,1421,0),(3,'Harry Potter knjige/filmi','Rada bi kupila vse knjige/filme od J.K. Rowling Harry Potter. V kolekciji imam še prve 3 knjige serije in 1. film, ostale pa bi rada kupila. Pišite samo resne stranke.',1647760653,1650352653,1,0),(4,'dasdas','Dsadasdasdsad',1647805370,1650397370,0,3),(5,'','Description',1647806809,1650398809,0,3),(6,'dasdas','Description',1647807019,1650399019,0,3),(7,'dasdsa','Description',1647807232,1650399232,0,3),(8,'dasdsa','Description',1647807333,1650399333,0,3),(9,'dsadasda','Description',1647807346,1650399346,0,3),(10,'dadas','Description',1647807984,1650399984,0,3),(11,'nekaj','seveda',1647808005,1650400005,0,3),(12,'nekaj','seveda',1647808046,1650400046,0,3),(13,'dasdas','adsasdasd',1647808172,1650400172,0,3),(14,'dadsa','Descriptiondasdas',1647808612,1650400612,0,3),(15,'dassdas','Descriptiondasdas',1647808618,1650400618,0,3),(16,'dassdas','Descriptiondasdas',1647808621,1650400621,0,3),(17,'dasdas','Description',1647808710,1650400710,0,3),(18,'dasdas','Description',1647808823,1650400823,0,3),(19,'dasdas','Description',1647808823,1650400823,0,3),(20,'dasdas','Description',1647808843,1650400843,0,3),(21,'dasdas','Description',1647808897,1650400897,0,3),(22,'dasdasd','Description',1647809172,1650401172,0,3),(23,'dasdasd','Description',1647809210,1650401210,0,3),(24,'Prosim','Description',1647809621,1650401621,0,3),(25,'dasdas','Description',1647810189,1650402189,0,3),(26,'dasdas','Description',1647810333,1650402333,0,3),(38,'dasdas','Descriptiondasd',1647814167,1650406167,0,4),(39,'dasdas','Descriptiondasd',1647814182,1650406182,0,4),(40,'dasdas','Descriptiondasd',1647814227,1650406227,0,4),(41,'dasdas','Descriptionsadas',1647814237,1650406237,0,4),(42,'dasdas','Descriptionsadas',1647814269,1650406269,0,4),(43,'dasda','Descriptionsadasdasdasa',1647814277,1650406277,0,4),(44,'dasda','Descriptionsadasdasdasa',1647814410,1650406410,0,4),(45,'dasda','Descriptionsadasdasdasa',1647814450,1650406450,0,4),(46,'dasdasd','Description',1647814472,1650406472,0,4),(47,'dasdasd','Description',1647814485,1650406485,0,4),(48,'dasdasd','Description',1647814486,1650406486,0,4),(49,'dasdas','Description',1647814499,1650406499,0,4),(50,'dasdas','Description',1647814584,1650406584,0,4),(51,'asdsadas','Description',1647814592,1650406592,0,4),(52,'asdsadas','Description',1647814674,1650406674,0,4),(53,'asdsadas','Description',1647815356,1650407356,0,4),(54,'asdsadas','Description',1647815358,1650407358,0,4),(55,'asdsadas','Description',1647815379,1650407379,0,4),(56,'asdsadas','Description',1647815539,1650407539,0,4),(57,'asdsadas','Description',1647815641,1650407641,0,4),(58,'asdsadas','Description',1647815714,1650407714,0,4),(59,'asdsadas','Description',1647815757,1650407757,0,4),(60,'asdsadas','Description',1647815832,1650407832,0,4),(61,'asdsadas','Description',1647815846,1650407846,0,4),(62,'asdsadas','Description',1647816118,1650408118,0,4),(63,'asdsadas','Description',1647816121,1650408121,0,4),(64,'asdsadas','Description',1647816147,1650408147,0,4),(65,'asdsadas','Description',1647816255,1650408255,0,4),(66,'asdsadas','Description',1647816270,1650408270,0,4),(67,'asdsadas','Description',1647816433,1650408433,0,4),(68,'asdsadas','Description',1647816442,1650408442,0,4),(69,'dadsa','Descriptiondsadasd',1647816452,1650408452,0,4),(70,'dadsa','Descriptiondsadasd',1647816528,1650455906,0,4);
        DB::table('ads')->insert([
            'title' => 'Kupim 10 kg pasje hrane Courigan',
            'description' => 'Prejšni mesec so prenehali izdelovati hrano podjetja Courigan, ki je bil moji psici Tački edina okusna hrana. Prodajalcu plačam dvakratno ceno nabavne cene, ki je znašala 5€ na kg.',
            'date_e' => Carbon::now()->addDays(30),
            'user_id' => 1
        ]);
    }
}
