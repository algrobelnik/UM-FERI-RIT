{{--dd($cats)--}}
{{$index++}}
@if (count($cats) > 0)
        @foreach($cats as $item)
            @if(!empty($item['name']))
                @isset($ad_cats)
                    <option value="{{$item['id']}}{{--/{{$index-1}}--}}" {{ ( in_array($item['id'], $ad_cats) ) ? 'selected' : '' }}>{{str_repeat("~~ ", $index-1)}}{{$item['name']}}</option>
                @else
                    <option value="{{$item['id']}}">{{str_repeat("~~ ", $index-1)}}{{$item['name']}}</option>
                @endisset
                @if($item['children'] != null)
                    @include('partials.categories', ['cats' => $item['children']])
                @endif
            @endif
    @endforeach
@else
    {{--dd($cats)--}}
@endif
