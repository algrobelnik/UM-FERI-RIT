<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Image extends Model
{
    protected $table = 'images';
    public $primaryKey = 'id';
    public $timestamps = true;

    public function ad(){
        return $this->belongsTo(Ad::class);
    }
}
