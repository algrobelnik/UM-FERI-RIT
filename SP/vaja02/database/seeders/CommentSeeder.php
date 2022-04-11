<?php

namespace Database\Seeders;

use Carbon\Carbon;
use Faker\Provider\Lorem;
use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;
use Nette\Utils\Random;

class CommentSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('comments')->insert([
            'email' => 'guest@guest.com',
            'alias' => 'guest' . Random::generate(10, '0-9'),
            'content' => Lorem::paragraph(),
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()->addDays(Random::generate(1, '0-9'))
        ]);
        DB::table('comments')->insert([
            'email' => 'guest@guest.com',
            'alias' => 'guest' . Random::generate(10, '0-9'),
            'content' => Lorem::paragraph(),
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()->addDays(Random::generate(1, '0-9'))
        ]);
        DB::table('comments')->insert([
            'email' => 'guest@guest.com',
            'alias' => 'guest' . Random::generate(10, '0-9'),
            'content' => Lorem::paragraph(),
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()->addDays(Random::generate(2, '0-9'))
        ]);
        DB::table('comments')->insert([
            'email' => 'guest@guest.com',
            'alias' => 'guest' . Random::generate(10, '0-9'),
            'content' => Lorem::paragraph(),
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()->addDays(Random::generate(2, '0-9'))
        ]);
        DB::table('comments')->insert([
            'email' => 'guest@guest.com',
            'alias' => 'guest' . Random::generate(10, '0-9'),
            'content' => Lorem::paragraph(),
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()
        ]);
        DB::table('comments')->insert([
            'email' => 'test@test.com',
            'alias' => 'testni zajček',
            'content' => 'Oglas je samo zgled za prikaz komentarjev',
            'ip_address' => '146.212.9.2',
            'ad_id' => 1,
            'created_at' => Carbon::now()->addDays(Random::generate(2, '0-9'))
        ]);
    }
}
