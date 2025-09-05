package com.example.looking4fight.fragments;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.appcompat.app.AppCompatActivity;
import com.example.looking4fight.R;
import com.example.looking4fight.SettingsFragment;
import com.example.looking4fight.databinding.ActivityMainBinding;
import com.google.android.material.bottomnavigation.BottomNavigationView;

public class MainActivity extends AppCompatActivity
{

    private ActivityMainBinding binding;

    // Initialize fragments
    private final Fragment exploreFragment = new ExploreFragment();
    private final Fragment profileFragment = new ProfileFragment();
    private final Fragment settingsFragment = new SettingsFragment();
    private final Fragment eventsFragment = new EventsFragment();

    private Fragment activeFragment = exploreFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());



        FragmentManager fragmentManager = getSupportFragmentManager();

        // Load fragments only if first launch
        if (savedInstanceState == null || true)
        {

            fragmentManager.beginTransaction()
                    .add(R.id.frameLayout, exploreFragment, "explore").commit();
            fragmentManager.beginTransaction()
                    .add(R.id.frameLayout, profileFragment, "profile").hide(profileFragment).commit();
            fragmentManager.beginTransaction()
                    .add(R.id.frameLayout, settingsFragment, "settings").hide(settingsFragment).commit();
            fragmentManager.beginTransaction()
                    .add(R.id.frameLayout, eventsFragment, "settings").hide(eventsFragment).commit();
        }
        else
        {
            // Restore active fragment after configuration change
            activeFragment = fragmentManager.findFragmentByTag(savedInstanceState.getString("activeFragment"));
        }

        // Set up bottom navigation
        binding.bottomNavigationView.setOnItemSelectedListener(item ->
        {
            if (item.getItemId() == R.id.createPost)
            {
                openCreatePostDialog(); // Open modal dialog
            }
            else
            {
                switchFragment(getSelectedFragment(item.getItemId()));
            }
            return true;
        });

        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomNavigationView);
        bottomNavigationView.setItemIconTintList(ContextCompat.getColorStateList(this, R.color.secondary_light));
    }

    private Fragment getSelectedFragment(int itemId)
    {
        if (itemId == R.id.home) return exploreFragment;
        if (itemId == R.id.profile) return profileFragment;
        if (itemId == R.id.settings) return settingsFragment;
        if (itemId == R.id.events) return eventsFragment;
        return exploreFragment; // Default
    }

    private void switchFragment(Fragment fragment)
    {
        if (fragment != activeFragment)
        {
            getSupportFragmentManager().beginTransaction()
                    .hide(activeFragment)
                    .show(fragment)
                    .commit();
            activeFragment = fragment;
        }
    }

    public void restoreBottomNavigationSelection() {
        new Handler(Looper.getMainLooper()).postDelayed(() -> {
            BottomNavigationView bottomNavigationView = findViewById(R.id.bottomNavigationView);
            int selectedItemId = bottomNavigationView.getSelectedItemId();
            bottomNavigationView.setSelectedItemId(selectedItemId);
        }, 100); // Small delay to ensure UI updates properly
    }

    private void openCreatePostDialog()
    {
        CreatePostDialogFragment createPostDialog = new CreatePostDialogFragment();
        createPostDialog.show(getSupportFragmentManager(), "CreatePostDialog");
    }

    @Override
    protected void onSaveInstanceState(Bundle outState)
    {
        super.onSaveInstanceState(outState);
        outState.putString("activeFragment", activeFragment.getTag());
    }
}
