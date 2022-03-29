<?php

namespace Database\Seeders;

use Carbon\Carbon;
use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class AdCategorySeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('ad_categories')->insert([
            'ad_id' => 1,
            'category_id' => 8
        ]);
        DB::table('ad_categories')->insert([
            'ad_id' => 1,
            'category_id' => 12
        ]);
    }
}
