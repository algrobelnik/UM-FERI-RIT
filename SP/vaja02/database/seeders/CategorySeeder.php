<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class CategorySeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('categories')->insert([
            'name' => 'sport'
        ]);
        DB::table('categories')->insert([
            'name' => 'news'
        ]);
        DB::table('categories')->insert([
            'name' => 'job/work'
        ]);
        DB::table('categories')->insert([
            'name' => 'clothes'
        ]);
        DB::table('categories')->insert([
            'name' => 'free time/hobbies'
        ]);
        DB::table('categories')->insert([
            'name' => 'music'
        ]);
        DB::table('categories')->insert([
            'name' => 'movies'
        ]);
        DB::table('categories')->insert([
            'name' => 'food'
        ]);
        DB::table('categories')->insert([
            'name' => 'books'
        ]);
        DB::table('categories')->insert([
            'name' => 'TV'
        ]);
        DB::table('categories')->insert([
            'name' => 'travel'
        ]);
        DB::table('categories')->insert([
            'name' => 'pets'
        ]);
        DB::table('categories')->insert([
            'name' => 'restaurant'
        ]);
        DB::table('categories')->insert([
            'name' => 'holiday'
        ]);
        DB::table('categories')->insert([
            'name' => 'basketball',
            'pid' => 1
        ]);
        DB::table('categories')->insert([
            'name' => 'hockey',
            'pid' => 1
        ]);
        DB::table('categories')->insert([
            'name' => 'golf',
            'pid' => 1
        ]);
        DB::table('categories')->insert([
            'name' => 'NBA',
            'pid' => 15
        ]);
        DB::table('categories')->insert([
            'name' => 'NHL',
            'pid' => 16
        ]);
    }
}
